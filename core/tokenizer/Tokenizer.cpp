#include "Tokenizer.h"

#include <boost/assert.hpp>

#include "core/Error.h"




Tokenizer::Tokenizer(const TokenizerRulesFacade & tokenizerRules, BufferedInputStream & inputStream)
	: mInputStream(inputStream),
	  mTokenizerRules(tokenizerRules),
	  mLastError(EC_NoError)
{
}



bool Tokenizer::getNextToken(Token & token)
{
	mInputStream.skipSpaces();

	int symbol = mInputStream.peek();
	if (symbol == InputStreamBase::EndOfFile)
	{
		/// end of stream
		return false;
	}

	TokenizerRulePtr tokenizerRule = mTokenizerRules.getTokenizerRule(symbol);
	if (!tokenizerRule)
	{
		return returnWithError(EC_NoParserRule);
	}

	tokenizerRule->init(mInputStream, token.lexeme);

	token.location = mInputStream.currentLocation();

	while ((symbol = mInputStream.peek()) != InputStreamBase::EndOfFile)
	{
		const TokenizerRuleState tokenizerRuleState = tokenizerRule->consumeSymbol();

		if (tokenizerRuleState == TRS_Finished)
		{
			break;
		}
		else if (tokenizerRuleState == TRS_Inapropriate)
		{
			mInputStream.unwind();
			break;
		}
	}

	switch (tokenizerRule->currentState())
	{
	case TRS_Finished:
		tokenizerRule->updateTokenTypeForToken(token);
		return true;
	}

	return returnWithError(tokenizerRule->lastError());
}



Error Tokenizer::lastError() const
{
	return mLastError;
}




/////////////////// Private implementation ///////////////////


bool Tokenizer::returnWithError(ErrorCodes ec)
{
	mLastError.errorCode = ec;
	mLastError.location = mInputStream.currentLocation();

	return false;
}


