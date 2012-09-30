#ifndef COMPILER_CORE_PARSER_RULES_H
#define COMPILER_CORE_PARSER_RULES_H

#include "core/Parser.h"



class AlphaNumParserRule : public ParserRuleBase
{
public:

	AlphaNumParserRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual ParserRuleState consumeSymbol(int symbol);

};


class DoubleQuotedTextParserRule : public ParserRuleBase
{
public:

	DoubleQuotedTextParserRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual ParserRuleState consumeSymbol(int symbol);

private:

	enum InternalState
	{
		IS_WaitFirstDoubleQuote,
		IS_WaitSecondDoubleQuote,
		IS_WaitEscapedSymbol,

		IS_WaitOctalValue1,
		IS_WaitOctalValue2,

		IS_WaitHexValue0,
		IS_WaitHexValue1,

		IS_Finished
	};

	InternalState mInternalState;


	unsigned int mTempForOctalValue;
	unsigned int mTempForHexValue;

	void consumeMaskedSymbol(int symbol);

	void consumeOctalValue1(int symbol);

	void consumeOctalValue2(int symbol);

	void consumeHexValue0(int symbol);

	void consumeHexValue1(int symbol);

};


template <int Symbol, TokenType tokenId>
class OneSymbolParserRule : public ParserRuleBase
{
public:

	OneSymbolParserRule()
		: ParserRuleBase(tokenId)
	{}

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


typedef OneSymbolParserRule<';', TK_Semicolon> SemicolonParserRule;

typedef OneSymbolParserRule<'*', TK_Star> StarParserRule;

typedef OneSymbolParserRule<'=', TK_Assignment> AssignmentParserRule;

typedef OneSymbolParserRule<'(', TK_OpenParen> OpenParenParserRule;
typedef OneSymbolParserRule<')', TK_CloseParen> CloseParenParserRule;

typedef OneSymbolParserRule<'{', TK_OpenBrace> OpenBraceParserRule;
typedef OneSymbolParserRule<'}', TK_CloseBrace> CloseBraceParserRule;

typedef OneSymbolParserRule<'[', TK_OpenBracket> OpenBracketParserRule;
typedef OneSymbolParserRule<']', TK_CloseBracket> CloseBracketParserRule;




#endif // COMPILER_CORE_PARSER_RULES_H
