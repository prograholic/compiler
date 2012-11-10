#ifndef COMPILER_CORE_TOKEN_H
#define COMPILER_CORE_TOKEN_H

#include <string>

#include "core/Location.h"


enum TokenType
{
	TK_Unknown,

	TK_AlphaNum,

	TK_IntegerConstant,
	TK_FloatingPointConstant,

	TK_DoubleQuotedText,

	TK_Semicolon,
	TK_Star,
	TK_Assignment,

	TK_OpenParen,
	TK_CloseParen,

	TK_OpenBrace,
	TK_CloseBrace,

	TK_OpenBracket,
	TK_CloseBracket,


	TK_RelationOperator,

	TK_Increment,

	/// reserved words (flow control)
	TK_Return,

	TK_If,
	TK_Else,

	TK_While,
	TK_Do,
	TK_For,

	TK_Continue,
	TK_Break,

	TK_Switch,
	TK_Case,
	TK_Default,

	TK_Goto,


	/// reserved words (builtin types and corresponding qualifiers)
	TK_Const,
	TK_Volatile,
	TK_Register,
	TK_Restricted,
	TK_Static,
	TK_Inline,

	TK_Signed,
	TK_Unsigned,

	TK_Void,
	TK_Char,
	TK_Short,
	TK_Int,
	TK_Long,

	TK_Float,
	TK_Double,



	/// reserved words (struct, enums, compond types)
	TK_Struct,
	TK_Enum,
	TK_Union,
	TK_Typedef,
	TK_Extern,
	TK_Auto,


	/// reserved words (other)
	TK_Sizeof
};



struct Token
{
	std::string lexeme;

	Location location;

	TokenType type;

	Token();

	Token(TokenType tokenType, const std::string & l, const Location & loc);
};

bool operator == (const Token & t1, const Token & t2);

inline bool operator != (const Token & t1, const Token & t2)
{
	return !(t1 == t2);
}



#endif // COMPILER_CORE_TOKEN_H
