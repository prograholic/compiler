#include "IntegerConstantTokenizerRule.h"

#include "SymbolClasses.h"



namespace
{
	bool inappropriateSymbol(const int symbol)
	{
		return std::isalnum(symbol) || (symbol == '_');
	}
}



IntegerConstantTokenizerRule::IntegerConstantTokenizerRule()
	: TokenizerRuleBase(TK_IntegerConstant, TRR_High),
	  mInternalState(IS_WaitFirstSymbol),
	  mSuffixType(0)
{
}

bool IntegerConstantTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return std::isdigit(firstSymbol);
}

TokenizerRuleState IntegerConstantTokenizerRule::consumeSymbol()
{
	const int symbol = mInputStream->peek();
	switch (mInternalState)
	{
	case IS_WaitFirstSymbol:
		onWaitFirstSymbol(symbol);
		break;

	case IS_FirstSymbolWasZero:
		onFirstSymbolWasZero(symbol);
		break;

	case IS_DecimalNumber:
		onDecimalNumber(symbol);
		break;

	case IS_OctalNumber:
		onOctalNumber(symbol);
		break;

	case IS_WaitForHexadecimalNumber:
		if (!std::isxdigit(symbol))
		{
			mCurrentState = TRS_Inapropriate;
			break;
		}
		/// @note does not need break here

	case IS_HexadecimalNumber:
		onHexadecimalNumber(symbol);

	case IS_Suffix:
		checkOptionalSuffix(symbol);
		break;
	}


	if (mCurrentState == TRS_Intermediate)
	{
		mInputStream->next();
	}

	return mCurrentState;
}



void IntegerConstantTokenizerRule::internalInit()
{
	mInternalState = IS_WaitFirstSymbol;
	mSuffixType = 0;
}



void IntegerConstantTokenizerRule::checkOptionalSuffix(const int symbol)
{
	mCurrentState = TRS_Intermediate;
	switch (symbol)
	{
	case 'u':
	case 'U':
		if (mSuffixType & ST_UnsignedBit)
		{
			mCurrentState = TRS_Inapropriate;
		}
		else
		{
			mInternalState = IS_Suffix;
			mHolder->push_back(symbol);
			mSuffixType |= ST_UnsignedBit;
		}
		break;


	case 'l':
	case 'L':
		if (mSuffixType & ST_SecondLongBit)
		{
			mCurrentState = TRS_Inapropriate;
			return;
		}

		mInternalState = IS_Suffix;

		if (mSuffixType & ST_FirstLongBit)
		{
			if ((*mHolder)[mHolder->size() - 1] != symbol)
			{
				mCurrentState = TRS_Inapropriate;
			}
			else
			{
				mSuffixType |= ST_SecondLongBit;
				mHolder->push_back(symbol);
			}
		}
		else
		{
			mSuffixType |= ST_FirstLongBit;
			mHolder->push_back(symbol);
		}
		break;


	default:
		if (inappropriateSymbol(symbol))
		{
			mCurrentState = TRS_Inapropriate;
		}
		else
		{
			mCurrentState = TRS_Finished;
		}
	}
}


///// state handlers


void IntegerConstantTokenizerRule::onWaitFirstSymbol(const int symbol)
{
	if (std::isdigit(symbol))
	{
		mHolder->push_back(symbol);
		if (symbol == '0')
		{
			mInternalState = IS_FirstSymbolWasZero;
		}
		else
		{
			mInternalState = IS_DecimalNumber;
		}

		mCurrentState = TRS_Intermediate;
	}
	else
	{
		mCurrentState = TRS_Inapropriate;
	}
}


void IntegerConstantTokenizerRule::onFirstSymbolWasZero(const int symbol)
{
	/// octal or hexadecimal numbers, or decimal number (0)

	mCurrentState = TRS_Intermediate;

	if (isOctal(symbol))
	{
		mHolder->push_back(symbol);
		mInternalState = IS_OctalNumber;
	}
	else
	{
		switch (symbol)
		{
		case '8':
		case '9':
			mCurrentState = TRS_Inapropriate;
			break;

		case 'x':
		case 'X':
			mInternalState = IS_WaitForHexadecimalNumber;
			break;

		default:
			checkOptionalSuffix(symbol);
			break;

		}
	}
}



void IntegerConstantTokenizerRule::onDecimalNumber(const int symbol)
{
	if (std::isdigit(symbol))
	{
		mHolder->push_back(symbol);
		mCurrentState = TRS_Intermediate;
	}
	else
	{
		checkOptionalSuffix(symbol);
	}
}




void IntegerConstantTokenizerRule::onOctalNumber(const int symbol)
{
	if (isOctal(symbol))
	{
		mHolder->push_back(symbol);
		mCurrentState = TRS_Intermediate;
		mInternalState = IS_OctalNumber;
	}
	else
	{
		checkOptionalSuffix(symbol);
	}
}

void IntegerConstantTokenizerRule::onHexadecimalNumber(const int symbol)
{
	if (std::isxdigit(symbol))
	{
		mHolder->push_back(symbol);
		mCurrentState = TRS_Intermediate;
		mInternalState = IS_HexadecimalNumber;
	}
	else
	{
		checkOptionalSuffix(symbol);
	}
}
