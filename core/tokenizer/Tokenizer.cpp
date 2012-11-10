#include "Tokenizer.h"

#include <boost/assert.hpp>
#include <boost/foreach.hpp>

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



	TokenizerRuleList ruleList = mTokenizerRules.getTokenizerRule(symbol);

	if (ruleList.empty())
	{
		return returnWithError(EC_NoParserRule);
	}

	BOOST_FOREACH(TokenizerRulePtr rule, ruleList)
	{
		if (processOneRule(symbol, rule, token))
		{
			mLastError.clear();
			return true;
		}
	}

	/// error already set in processOneRule
	return false;
}



bool Tokenizer::processOneRule(int symbol, TokenizerRulePtr rule, Token & token)
{
	rule->init(mInputStream, token.lexeme);

	token.location = mInputStream.currentLocation();

	while ((symbol = mInputStream.peek()) != InputStreamBase::EndOfFile)
	{
		const TokenizerRuleState tokenizerRuleState = rule->consumeSymbol();

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

	switch (rule->currentState())
	{
	case TRS_Finished:
		rule->updateTokenTypeForToken(token);
		return true;
	}

	return returnWithError(rule->lastError());
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


