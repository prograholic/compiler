#ifndef COMPILER_CORE_TOKENIZER_RULES_ONE_SYMBOL_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_ONE_SYMBOL_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

template <int Symbol, TokenType tokenId, ErrorCodes ec>
class OneSymbolTokenizerRule : public TokenizerRuleBase
{
public:

	OneSymbolTokenizerRule()
		: TokenizerRuleBase(tokenId)
	{}

	virtual bool firstSymbolFits(int firstSymbol)
	{
		return firstSymbol == Symbol;
	}

	virtual TokenizerRuleState consumeSymbol()
	{
		int symbol = mInputStream->next();

		if (symbol == Symbol)
		{
			mCurrentState = TRS_Finished;
		}
		else
		{
			mCurrentState = TRS_Inapropriate;
			mLastError = ec;
		}

		return mCurrentState;
	}
};


typedef OneSymbolTokenizerRule<';', TK_Semicolon,    EC_WrongSemicolonSymbol>    SemicolonTokenizerRule;

typedef OneSymbolTokenizerRule<'*', TK_Star,         EC_WrongStarSymbol>         StarTokenizerRule;

typedef OneSymbolTokenizerRule<'(', TK_OpenParen,    EC_WrongOpenParenSymbol>    OpenParenTokenizerRule;
typedef OneSymbolTokenizerRule<')', TK_CloseParen,   EC_WrongCloseParenSymbol>   CloseParenTokenizerRule;

typedef OneSymbolTokenizerRule<'{', TK_OpenBrace,    EC_WrongOpenBraceSymbol>    OpenBraceTokenizerRule;
typedef OneSymbolTokenizerRule<'}', TK_CloseBrace,   EC_WrongCloseBraceSymbol>   CloseBraceTokenizerRule;

typedef OneSymbolTokenizerRule<'[', TK_OpenBracket,  EC_WrongOpenBracketSymbol>  OpenBracketTokenizerRule;
typedef OneSymbolTokenizerRule<']', TK_CloseBracket, EC_WrongCloseBracketSymbol> CloseBracketTokenizerRule;






#endif // COMPILER_CORE_TOKENIZER_RULES_ONE_SYMBOL_TOKENIZER_RULE_H
