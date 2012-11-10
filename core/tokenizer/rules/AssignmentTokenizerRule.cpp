#include "AssignmentTokenizerRule.h"

namespace
{
	const int assignmentValue = '=';
}

AssignmentTokenizerRule::AssignmentTokenizerRule()
	: TokenizerRuleBase(TK_Assignment)
{
}


bool AssignmentTokenizerRule::firstSymbolFits(int firstSymbol)
{
	return firstSymbol == assignmentValue;
}


TokenizerRuleState AssignmentTokenizerRule::consumeSymbol()
{
	const int symbol = mInputStream->next();

	if (symbol == assignmentValue)
	{
		const int nextSymbol = mInputStream->peek();
		if (nextSymbol == assignmentValue)
		{
			mCurrentState = TRS_Inapropriate;
		}
		else
		{
			mHolder->push_back(symbol);
			mCurrentState = TRS_Finished;
		}
	}
	else
	{
		mCurrentState = TRS_Inapropriate;
	}

	return mCurrentState;
}
