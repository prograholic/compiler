#include "core/ParserRules.h"




bool AlphaNumParserRule::firstSymbolFits(int firstSymbol)
{
	return std::isalnum(firstSymbol);
}

ParserRuleState AlphaNumParserRule::consumeSymbol(int symbol)
{
	if (std::isalnum(symbol))
	{
		mHolder->push_back(symbol);
		mCurrentState = PRS_Intermediate;
	}
	else if (symbol == std::istream::traits_type::eof())
	{
		mCurrentState = PRS_Finished;
	}
	else
	{
		mCurrentState = PRS_FinishedWithUnget;
	}

	return mCurrentState;
}


////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////
