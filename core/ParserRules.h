#ifndef COMPILER_CORE_PARSER_RULES_H
#define COMPILER_CORE_PARSER_RULES_H

#include "core/Parser.h"



class AlphaNumParserRule : public ParserRuleBase
{
public:

	virtual bool firstSymbolFits(int firstSymbol);

	virtual ParserRuleState consumeSymbol(int symbol);

};


template <int Symbol>
class OneSymbolParserRule : public ParserRuleBase
{
public:
	virtual bool firstSymbolFits(int firstSymbol)
	{
		return firstSymbol == Symbol;
	}

	virtual ParserRuleState consumeSymbol(int symbol)
	{
		if (symbol == Symbol)
		{
			mHolder->push_back(symbol);
			mCurrentState = PRS_Finished;
		}
		else
		{
			mCurrentState = PRS_Inapropriate;
		}

		return mCurrentState;
	}
};


typedef OneSymbolParserRule<';'> SemicolonParserRule;

typedef OneSymbolParserRule<'*'> StarParserRule;

typedef OneSymbolParserRule<'('> OpenParenParserRule;
typedef OneSymbolParserRule<')'> CloseParenParserRule;

typedef OneSymbolParserRule<'{'> OpenBraceParserRule;
typedef OneSymbolParserRule<'}'> CloseBraceParserRule;




#endif // COMPILER_CORE_PARSER_RULES_H
