#include "AlphaNumTokenizerRule.h"

#include "SymbolClasses.h"

AlphaNumTokenizerRule::AlphaNumTokenizerRule()
	: TokenizerRuleBase(TK_AlphaNum),
	  mIsEmpty(true)
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
		mIsEmpty = false;
		mCurrentState = TRS_Intermediate;

		mInputStream->next();
	}
	else
	{
		if (mIsEmpty)
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



void AlphaNumTokenizerRule::internalInit()
{
	mIsEmpty = true;
}
