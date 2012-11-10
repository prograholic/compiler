#include "IncrementDecrementTokenizerRule.h"

IncrementDecrementTokenizerRule::IncrementDecrementTokenizerRule(int requiredSymbol)
	: TokenizerRuleBase((requiredSymbol == '+') ? TK_Increment : TK_Decrement),
	  mInternalState(IS_WaitFirstSymbol),
	  mRequiredSymbol(requiredSymbol)
{
}

bool IncrementDecrementTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return (firstSymbol == mRequiredSymbol);
}

TokenizerRuleState IncrementDecrementTokenizerRule::consumeSymbol()
{
	const int symbol = mInputStream->peek();

	if (symbol != mRequiredSymbol)
	{
		mCurrentState = TRS_Inapropriate;
	}
	else
	{
		mHolder->push_back(symbol);
		mInputStream->next();
		switch (mInternalState)
		{
		case IS_WaitFirstSymbol:
			mInternalState = IS_WaitSecondSymbol;
			mCurrentState = TRS_Intermediate;
			break;

		case IS_WaitSecondSymbol:
			if (mInputStream->peek() == mRequiredSymbol)
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

void IncrementDecrementTokenizerRule::internalInit()
{
	mInternalState = IS_WaitFirstSymbol;
}
