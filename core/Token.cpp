#include "Token.h"


Token::Token()
	: lexeme(),
	  location(),
	  type(TK_Unknown)
{}

Token::Token(TokenType tokenType, const std::string & l, const TokenLocation & loc)
	: lexeme(l),
	  location(loc),
	  type(tokenType)
{}


bool operator == (const Token & t1, const Token & t2)
{
	if (t1.type != t2.type)
	{
		return false;
	}

	if (t1.lexeme != t2.lexeme)
	{
		return false;
	}

	if (t1.location != t2.location)
	{
		return false;
	}

	return true;
}
