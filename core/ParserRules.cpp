#include "core/ParserRules.h"

#include <boost/smart_ptr/make_shared.hpp>



AlphaNumParserRule::AlphaNumParserRule()
	: ParserRuleBase(TK_AlphaNum)
{
}


bool AlphaNumParserRule::firstSymbolFits(int firstSymbol)
{
	return std::isalnum(firstSymbol);
}

ParserRuleState AlphaNumParserRule::consumeSymbol()
{
	int symbol = mInputStream->peek();

	if (std::isalnum(symbol))
	{
		mHolder->push_back(symbol);
		mCurrentState = PRS_Intermediate;

		mInputStream->next();
	}
	else
	{
		if (mHolder->empty())
		{
			mCurrentState = PRS_Inapropriate;
		}
		else
		{
			mCurrentState = PRS_Finished;
		}
	}

	return mCurrentState;
}


////////////////////////////////////////////////////////////////////////////////////////////////////


DoubleQuotedTextParserRule::DoubleQuotedTextParserRule()
	: ParserRuleBase(TK_DoubleQuotedText),
	  mInternalState(IS_WaitFirstDoubleQuote),
	  mTempForOctalValue(0),
	  mTempForHexValue(0)
{
}


bool DoubleQuotedTextParserRule::firstSymbolFits(int firstSymbol)
{
	return firstSymbol == '\"';
}

ParserRuleState DoubleQuotedTextParserRule::consumeSymbol()
{
	int symbol = mInputStream->next();

	switch (mInternalState)
	{
	case IS_WaitFirstDoubleQuote:
		if (symbol != '\"')
		{
			mCurrentState = PRS_Inapropriate;
		}
		else
		{
			mInternalState = IS_WaitSecondDoubleQuote;
			mCurrentState = PRS_Intermediate;
		}
		break;

	case IS_WaitSecondDoubleQuote:
		if (symbol != '\"')
		{
			/// found escape symbol
			if (symbol == '\\')
			{
				mInternalState = IS_WaitEscapedSymbol;
			}
			else
			{
				mHolder->push_back(symbol);
			}
		}
		else
		{
			mCurrentState = PRS_Finished;
		}
		break;

	case IS_WaitEscapedSymbol:
		mTempForOctalValue = 0;
		mTempForHexValue = 0;
		consumeMaskedSymbol(symbol);
		break;

	case IS_WaitOctalValue1:
		consumeOctalValue1(symbol);
		break;

	case IS_WaitOctalValue2:
		consumeOctalValue2(symbol);
		break;


	case IS_WaitHexValue0:
		consumeHexValue0(symbol);
		break;

	case IS_WaitHexValue1:
		consumeHexValue1(symbol);
		break;

	}

	return mCurrentState;
}


void DoubleQuotedTextParserRule::consumeMaskedSymbol(int symbol)
{
	bool escapingFinished = true;

	switch (symbol)
	{
	case 'a':
		mHolder->push_back('\a');
		break;

	case 'b':
		mHolder->push_back('\b');
		break;

	case 'f':
		mHolder->push_back('\f');
		break;

	case 'n':
		mHolder->push_back('\n');
		break;

	case 'r':
		mHolder->push_back('\r');
		break;

	case 't':
		mHolder->push_back('\t');
		break;

	case 'v':
		mHolder->push_back('\v');
		break;

	case '\'':
		mHolder->push_back('\'');
		break;

	case '\"':
		mHolder->push_back('\"');
		break;

	case '\\':
		mHolder->push_back('\\');
		break;

	case '\?':
		mHolder->push_back('\?');
		break;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		mTempForOctalValue = (symbol - '0') * 64;
		mInternalState = IS_WaitOctalValue1;
		escapingFinished = false;
		break;

	case 'x':
		mInternalState = IS_WaitHexValue0;
		escapingFinished = false;
		break;

	default:
		mCurrentState = PRS_Inapropriate;
		mLastError = EC_WrongMaskedSymbol;
		escapingFinished = false;
	}


	if (escapingFinished)
	{
		mInternalState = IS_WaitSecondDoubleQuote;
	}
}



void DoubleQuotedTextParserRule::consumeOctalValue1(int symbol)
{
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		mTempForOctalValue += ((symbol - '0') * 8);
		mInternalState = IS_WaitOctalValue2;
		break;

	default:
		/// if previous symbol was 0, then this is end of C string
		if (mTempForOctalValue == 0)
		{
			mHolder->push_back('\0');
			if (symbol == '\"')
			{
				/// received second double quote, stopping parsing
				mCurrentState = PRS_Finished;
			}
		}
		else
		{
			mCurrentState = PRS_Inapropriate;
			mLastError = EC_WrongOctalSymbol;
		}
	}
}


void DoubleQuotedTextParserRule::consumeOctalValue2(int symbol)
{
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		mTempForOctalValue += (symbol - '0');
		mInternalState = IS_WaitSecondDoubleQuote;
		mHolder->push_back(mTempForOctalValue);
		mTempForOctalValue = 0;
		break;

	default:
		mCurrentState = PRS_Inapropriate;
		mLastError = EC_WrongOctalSymbol;
	}
}


void DoubleQuotedTextParserRule::consumeHexValue0(int symbol)
{
	int val = -1;
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '8':
	case '9':
		val = symbol - '0';
		BOOST_ASSERT(val >= 0);
		break;

	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		val = (symbol - 'a') + 10;
		BOOST_ASSERT(val >= 0);
		break;

	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		val = (symbol - 'A') + 10;
		BOOST_ASSERT(val >= 0);
		break;

	default:
		mCurrentState = PRS_Inapropriate;
		mLastError = EC_WrongHexSymbol;
	}

	if (val >= 0)
	{
		mTempForHexValue = (val * 16);
		mInternalState = IS_WaitHexValue1;
	}
}


void DoubleQuotedTextParserRule::consumeHexValue1(int symbol)
{
	int val = -1;
	switch (symbol)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '8':
	case '9':
		val = symbol - '0';
		BOOST_ASSERT(val >= 0);
		break;

	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		val = (symbol - 'a') + 10;
		BOOST_ASSERT(val >= 0);
		break;

	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		val = (symbol - 'A') + 10;
		BOOST_ASSERT(val >= 0);
		break;

	default:
		mCurrentState = PRS_Inapropriate;
		mLastError = EC_WrongHexSymbol;
	}

	if (val >= 0)
	{
		mTempForHexValue += val;
		mInternalState = IS_WaitSecondDoubleQuote;

		mHolder->push_back(mTempForHexValue);
		mTempForHexValue = 0;
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////


RelationOperatorParserRule::RelationOperatorParserRule()
	: ParserRuleBase(TK_RelationOperator)
{

}


bool RelationOperatorParserRule::firstSymbolFits(int firstSymbol)
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

ParserRuleState RelationOperatorParserRule::consumeSymbol()
{
	const int symbol = mInputStream->peek();

	switch (mInternalState)
	{
	case IS_WaitFirstSymbol:
		if (firstSymbolFits(symbol))
		{
			mHolder->push_back(symbol);
			mInputStream->next();
			mCurrentState = PRS_Intermediate;
			mInternalState = IS_WaitSecondSymbol;
		}
		else
		{
			mCurrentState = PRS_Inapropriate;
		}
		break;

	case IS_WaitSecondSymbol:
		BOOST_ASSERT(!mHolder->empty());
		switch ((*mHolder)[0])
		{
		case '<':
		case '>':
			if (!firstSymbolFits(symbol))
			{
				/// symbol does not belongs to our token
				mCurrentState = PRS_Finished;
				break;
			}
			else
			{
				/// allowed only <= or >=
				if (symbol == '=')
				{
					mHolder->push_back(symbol);
					mCurrentState = PRS_Finished;
					mInputStream->next();
				}
				else
				{
					mCurrentState = PRS_Inapropriate;
				}
			}
			break;

		case '=':
		case '!':
			if (symbol != '=')
			{
				mCurrentState = PRS_Inapropriate;
			}
			else
			{
				mCurrentState = PRS_Finished;
				mHolder->push_back(symbol);
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



void RelationOperatorParserRule::internalInit()
{
	mInternalState = IS_WaitFirstSymbol;
}

////////////////////////////////////////////////////////////////////////////////////////////////////


ParserRuleList getParserRuleList()
{
	ParserRuleList result;

	result.push_back(boost::make_shared<AlphaNumParserRule>());
	result.push_back(boost::make_shared<DoubleQuotedTextParserRule>());

	result.push_back(boost::make_shared<SemicolonParserRule>());

	result.push_back(boost::make_shared<StarParserRule>());

	result.push_back(boost::make_shared<AssignmentParserRule>());


	result.push_back(boost::make_shared<OpenParenParserRule>());
	result.push_back(boost::make_shared<CloseParenParserRule>());

	result.push_back(boost::make_shared<OpenBraceParserRule>());
	result.push_back(boost::make_shared<CloseBraceParserRule>());

	result.push_back(boost::make_shared<OpenBracketParserRule>());
	result.push_back(boost::make_shared<CloseBracketParserRule>());

	result.push_back(boost::make_shared<RelationOperatorParserRule>());

	return result;
}
