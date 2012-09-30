#include "Parser.h"

#include <boost/assert.hpp>


TokenLocation::TokenLocation()
	: line(0),
	  colon(0)
{}

TokenLocation::TokenLocation(size_t l, size_t c)
	: line(l),
	  colon(c)
{}


bool operator == (const TokenLocation & tl1, const TokenLocation & tl2)
{
	if (tl1.colon != tl2.colon)
	{
		return false;
	}

	if (tl1.line != tl2.line)
	{
		return false;
	}

	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////



Token::Token()
	: lexeme(),
	  loc()
{}

Token::Token(const std::string & l, const TokenLocation & lc)
	: lexeme(l),
	  loc(lc)
{}


bool operator == (const Token & t1, const Token & t2)
{
	if (t1.lexeme != t2.lexeme)
	{
		return false;
	}

	if (t1.loc != t2.loc)
	{
		return false;
	}

	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////



ParserRuleBase::ParserRuleBase()
	: mHolder(0),
	  mCurrentState(PRS_Unknown)
{
}

ParserRuleBase::~ParserRuleBase()
{
}



void ParserRuleBase::init(std::string & holder)
{
	mHolder = &holder;
	mCurrentState = PRS_Unknown;
}


ParserRuleState ParserRuleBase::currentState()
{
	return mCurrentState;
}


Parser::Parser(const ParserRuleList & parserRuleList, std::istream & inputStream)
	: mInputStream(inputStream),
	  mCurrentLocation(),
	  mParserRuleList(parserRuleList)
{
}



bool Parser::getNextToken(Token & token)
{
	skipSpaces();

	int symbol = mInputStream.peek();
	if (symbol == std::istream::traits_type::eof())
	{
		/// end of stream
		return false;
	}

	ParserRulePtr parserRule = getParserRule(symbol);
	if (!parserRule)
	{
		/// @todo: add error information
		return false;
	}

	parserRule->init(token.lexeme);

	token.loc = mCurrentLocation;

	while ((symbol = mInputStream.get()) != std::istream::traits_type::eof())
	{
		const ParserRuleState parserRuleState = parserRule->consumeSymbol(symbol);

		if (parserRuleState != PRS_Intermediate)
		{
			if (parserRuleState == PRS_FinishedWithUnget)
			{
				mInputStream.unget();
			}
			else
			{
				updateCurrentLocation(symbol);
			}
			break;
		}

		updateCurrentLocation(symbol);
	}

	if (symbol == std::istream::traits_type::eof())
	{
		/// process EOF
		parserRule->consumeSymbol(symbol);
	}


	switch (parserRule->currentState())
	{
	case PRS_Finished:
	case PRS_FinishedWithUnget:
		return true;
	}

	return false;
}


void Parser::updateCurrentLocation(int symbol)
{
	if (symbol == '\n')
	{
		++mCurrentLocation.line;
		mCurrentLocation.colon = 0;
	}
	else
	{
		++mCurrentLocation.colon;
	}
}


ParserRulePtr Parser::getParserRule(int firstSymbol) const
{
	for (ParserRuleList::const_iterator it = mParserRuleList.begin(); it != mParserRuleList.end(); ++it)
	{
		if ((*it)->firstSymbolFits(firstSymbol))
		{
			return *it;
		}
	}

	return ParserRulePtr();
}



void Parser::skipSpaces()
{
	int symbol;

	while ((symbol = mInputStream.get()) != std::istream::traits_type::eof())
	{
		if (!std::isspace(symbol))
		{
			mInputStream.unget();
			return;
		}
		updateCurrentLocation(symbol);
	}
}


