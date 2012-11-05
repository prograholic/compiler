#include "AlphaNumTokenizerRule.h"

AlphaNumTokenizerRule::AlphaNumTokenizerRule()
	: TokenizerRuleBase(TK_AlphaNum)
{
}


bool AlphaNumTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return std::isalnum(firstSymbol);
}

TokenizerRuleState AlphaNumTokenizerRule::consumeSymbol()
{
	int symbol = mInputStream->peek();

	if (std::isalnum(symbol))
	{
		mHolder->push_back(symbol);
		mCurrentState = TRS_Intermediate;

		mInputStream->next();
	}
	else
	{
		if (mHolder->empty())
		{
			mCurrentState = TRS_Inapropriate;
		}
		else
		{
			mCurrentState = TRS_Finished;
		}
	}

	return mCurrentState;
}
