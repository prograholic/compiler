#include "Parser.h"

#include <boost/assert.hpp>

#include "Error.h"




Parser::Parser(const ParserRuleList & parserRuleList, BufferedInputStream & inputStream)
	: mInputStream(inputStream),
	  mParserRuleList(parserRuleList),
	  mLastError(EC_NoError)
{
}



bool Parser::getNextToken(Token & token)
{
	mInputStream.skipSpaces();

	int symbol = mInputStream.peek();
	if (symbol == InputStreamBase::EndOfFile)
	{
		/// end of stream
		return false;
	}

	ParserRulePtr parserRule = getParserRule(symbol);
	if (!parserRule)
	{
		return returnWithError(EC_NoParserRule);
	}

	parserRule->init(mInputStream, token.lexeme);

	token.location = mInputStream.currentLocation();

	while ((symbol = mInputStream.peek()) != InputStreamBase::EndOfFile)
	{
		const ParserRuleState parserRuleState = parserRule->consumeSymbol();

		if (parserRuleState == PRS_Finished)
		{
			break;
		}
		else if (parserRuleState == PRS_Inapropriate)
		{
			mInputStream.unwind();
			break;
		}
	}

	switch (parserRule->currentState())
	{
	case PRS_Finished:
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



bool Parser::returnWithError(ErrorCodes ec)
{
	mLastError.errorCode = ec;
	mLastError.location = mInputStream.currentLocation();

	return false;
}


