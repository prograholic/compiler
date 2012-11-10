#include "PredefinedNameTokenizerRule.h"

#include <boost/assert.hpp>

PredefinedNameTokenizerRule::PredefinedNameTokenizerRule(TokenType tokenType, const std::string & predefinedName)
	: TokenizerRuleBase(tokenType, TRR_High),
	  mPredefinedName(predefinedName),
	  mCurrentSymbolPosition(0)
{
	BOOST_ASSERT(!mPredefinedName.empty());
}


bool PredefinedNameTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return firstSymbol == mPredefinedName[0];
}

TokenizerRuleState PredefinedNameTokenizerRule::consumeSymbol()
{
	int symbol = mInputStream->next();

	if (mCurrentSymbolPosition == (mPredefinedName.size() - 1))
	{
		if (mPredefinedName[mCurrentSymbolPosition] == symbol)
		{
			symbol = mInputStream->peek();
			/// perform lookahead for one symbol
			if (std::isalnum(symbol))
			{
				/// cannot have alpha or numeric symbol
				mCurrentState = TRS_Inapropriate;
			}
			else
			{
				*mHolder = mPredefinedName;
				mCurrentState = TRS_Finished;
			}
		}
	}
	else
	{
		BOOST_ASSERT(mCurrentSymbolPosition < mPredefinedName.size());

		if (mPredefinedName[mCurrentSymbolPosition] == symbol)
		{
			++mCurrentSymbolPosition;
			mCurrentState = TRS_Intermediate;
		}
		else
		{
			mCurrentState = TRS_Inapropriate;
		}
	}

	return mCurrentState;
}




void PredefinedNameTokenizerRule::internalInit()
{
	mCurrentSymbolPosition = 0;
}
