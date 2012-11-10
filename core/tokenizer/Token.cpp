#include "core/tokenizer/Token.h"


Token::Token()
	: lexeme(),
	  location(),
	  type(TK_Unknown),
	  advancedLexemeValue()
{
}

Token::Token(TokenType tokenType, const StringRef & l, const Location & loc)
	: lexeme(l),
	  location(loc),
	  type(tokenType),
	  advancedLexemeValue()
{

}


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

/*	if (t1.advancedLexemeValue != t2.advancedLexemeValue)
	{
		return false;
	}
*/
	return true;
}
