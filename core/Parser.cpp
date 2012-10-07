#include "Parser.h"

#include <boost/assert.hpp>

#include "Error.h"




Parser::Parser(const ParserRuleList & parserRuleList, std::istream & inputStream)
	: mInputStream(inputStream),
	  mCurrentLocation(),
	  mParserRuleList(parserRuleList),
	  mLastError(EC_NoError, mCurrentLocation)
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
		return returnWithError(EC_NoParserRule);
	}

	parserRule->init(token.lexeme);

	token.location = mCurrentLocation;

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
		parserRule->updateTokenTypeForToken(token);
		return true;
	}

	return returnWithError(parserRule->lastError());
}



Error Parser::lastError() const
{
	return mLastError;
}




/////////////////// Private implementation ///////////////////





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


bool Parser::returnWithError(ErrorCodes ec)
{
	mLastError.errorCode = ec;
	mLastError.location = mCurrentLocation;

	return false;
}


