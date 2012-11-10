#include "AlphaNumTokenizerRule.h"

#include "SymbolClasses.h"

AlphaNumTokenizerRule::AlphaNumTokenizerRule()
	: TokenizerRuleBase(TK_AlphaNum)
{
}


bool AlphaNumTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return fitsAsIdentifier(firstSymbol, true);
}

TokenizerRuleState AlphaNumTokenizerRule::consumeSymbol()
{
	int symbol = mInputStream->peek();

	if (fitsAsIdentifier(symbol))
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
