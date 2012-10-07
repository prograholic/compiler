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


template <int Symbol, TokenType tokenId, ErrorCodes ec>
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
			mLastError = ec;
		}

		return mCurrentState;
	}
};


typedef OneSymbolParserRule<';', TK_Semicolon,    EC_WrongSemicolonSymbol>    SemicolonParserRule;

typedef OneSymbolParserRule<'*', TK_Star,         EC_WrongStarSymbol>         StarParserRule;

typedef OneSymbolParserRule<'=', TK_Assignment,   EC_WrongAssignmentSymbol>   AssignmentParserRule;

typedef OneSymbolParserRule<'(', TK_OpenParen,    EC_WrongOpenParenSymbol>    OpenParenParserRule;
typedef OneSymbolParserRule<')', TK_CloseParen,   EC_WrongCloseParenSymbol>   CloseParenParserRule;

typedef OneSymbolParserRule<'{', TK_OpenBrace,    EC_WrongOpenBraceSymbol>    OpenBraceParserRule;
typedef OneSymbolParserRule<'}', TK_CloseBrace,   EC_WrongCloseBraceSymbol>   CloseBraceParserRule;

typedef OneSymbolParserRule<'[', TK_OpenBracket,  EC_WrongOpenBracketSymbol>  OpenBracketParserRule;
typedef OneSymbolParserRule<']', TK_CloseBracket, EC_WrongCloseBracketSymbol> CloseBracketParserRule;




#endif // COMPILER_CORE_PARSER_RULES_H
