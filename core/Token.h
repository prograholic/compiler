#ifndef COMPILER_CORE_TOKEN_H
#define COMPILER_CORE_TOKEN_H

#include <string>

#include "core/TokenLocation.h"


enum TokenType
{
	TK_Unknown,

	TK_AlphaNum,
	TK_DoubleQuotedText,

	TK_Semicolon,
	TK_Star,
	TK_Assignment,

	TK_OpenParen,
	TK_CloseParen,

	TK_OpenBrace,
	TK_CloseBrace,

	TK_OpenBracket,
	TK_CloseBracket
};



struct Token
{
	std::string lexeme;

	TokenLocation location;

	TokenType type;

	Token();

	Token(TokenType tokenType, const std::string & l, const TokenLocation & loc);
};

bool operator == (const Token & t1, const Token & t2);

inline bool operator != (const Token & t1, const Token & t2)
{
	return !(t1 == t2);
}



#endif // COMPILER_CORE_TOKEN_H
