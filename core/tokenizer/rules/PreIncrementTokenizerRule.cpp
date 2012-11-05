#include "PreIncrementTokenizerRule.h"


const int requiredSymbol = '+';

PreIncrementTokenizerRule::PreIncrementTokenizerRule()
	: TokenizerRuleBase(TK_PreIncrement),
	  mInternalState(IS_WaitFirstPlus)
{
}

bool PreIncrementTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return (firstSymbol == requiredSymbol);
}

TokenizerRuleState PreIncrementTokenizerRule::consumeSymbol()
{
	const int symbol = mInputStream->peek();

	if (symbol != requiredSymbol)
	{
		mCurrentState = TRS_Inapropriate;
	}
	else
	{
		mHolder->push_back(symbol);
		mInputStream->next();
		switch (mInternalState)
		{
		case IS_WaitFirstPlus:
			mInternalState = IS_WaitSecondPlus;
			mCurrentState = TRS_Intermediate;
			break;

		case IS_WaitSecondPlus:
			if (mInputStream->peek() == requiredSymbol)
			{
				/// Three or more consequent symbols is not allowed
				mCurrentState = TRS_Inapropriate;
			}
			else
			{
				mCurrentState = TRS_Finished;
			}
			break;


		default:
			BOOST_ASSERT(0 && "unknown internal state");
		}
	}

	return mCurrentState;
}

void PreIncrementTokenizerRule::internalInit()
{
	mInternalState = IS_WaitFirstPlus;
}
