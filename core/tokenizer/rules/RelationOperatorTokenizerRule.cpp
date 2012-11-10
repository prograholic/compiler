#include "core/tokenizer/rules/RelationOperatorTokenizerRule.h"

RelationOperatorTokenizerRule::RelationOperatorTokenizerRule()
	: TokenizerRuleBase(TK_RelationOperator),
	  mFirstSymbol(0)
{

}


bool RelationOperatorTokenizerRule::firstSymbolFits(int firstSymbol)
{
	switch (firstSymbol)
	{
	case '<':
	case '>':
	case '!':
	case '=':
		return true;

	default:
		return false;
	}
}

TokenizerRuleState RelationOperatorTokenizerRule::consumeSymbol()
{
	const int symbol = mInputStream->peek();

	switch (mInternalState)
	{
	case IS_WaitFirstSymbol:
		if (firstSymbolFits(symbol))
		{
			mFirstSymbol = symbol;
			mInputStream->next();
			mCurrentState = TRS_Intermediate;
			mInternalState = IS_WaitSecondSymbol;
		}
		else
		{
			mCurrentState = TRS_Inapropriate;
		}
		break;

	case IS_WaitSecondSymbol:
		switch (mFirstSymbol)
		{
		case '<':
		case '>':
			if (!firstSymbolFits(symbol))
			{
				/// symbol does not belongs to our token
				mCurrentState = TRS_Finished;
				break;
			}
			else
			{
				/// allowed only <= or >=
				if (symbol == '=')
				{
					mCurrentState = TRS_Finished;
					mInputStream->next();
				}
				else
				{
					mCurrentState = TRS_Inapropriate;
				}
			}
			break;

		case '=':
		case '!':
			if (symbol != '=')
			{
				mCurrentState = TRS_Inapropriate;
			}
			else
			{
				mCurrentState = TRS_Finished;
				mInputStream->next();
			}
			break;

		default:
			BOOST_ASSERT(0 && "holder cannot hold unknown symbol");
			break;
		}

		break;

	}

	return mCurrentState;
}



void RelationOperatorTokenizerRule::internalInit()
{
	mInternalState = IS_WaitFirstSymbol;
	mFirstSymbol = 0;
}
