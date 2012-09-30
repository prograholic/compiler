#ifndef COMPILER_CORE_PARSER_H
#define COMPILER_CORE_PARSER_H

#include <istream>
#include <string>
#include <list>

#include <boost/noncopyable.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>




struct TokenLocation
{
	size_t line;
	size_t colon;

	TokenLocation();

	TokenLocation(size_t l, size_t c);
};


bool operator == (const TokenLocation & tl1, const TokenLocation & tl2);

inline bool operator != (const TokenLocation & tl1, const TokenLocation & tl2)
{
	return !(tl1 == tl2);
}



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







enum ParserRuleState
{
	PRS_Unknown,
	PRS_Intermediate,
	PRS_Finished,
	PRS_FinishedWithUnget,
	PRS_Inapropriate
};


class ParserRuleBase : private boost::noncopyable
{
public:

	ParserRuleBase(TokenType tokenType);

	virtual ~ParserRuleBase();


	ParserRuleState currentState();

	void setTokenType(Token & token);

	TokenType tokenType() const;

	virtual void init(std::string & holder);


	virtual bool firstSymbolFits(int firstSymbol) = 0;

	virtual ParserRuleState consumeSymbol(int symbol) = 0;


protected:

	std::string * mHolder;
	ParserRuleState mCurrentState;
	TokenType mTokenType;

};


typedef boost::shared_ptr<ParserRuleBase> ParserRulePtr;


typedef std::list<ParserRulePtr> ParserRuleList;


class Parser : private boost::noncopyable
{
public:
	Parser(const ParserRuleList & parserRuleList, std::istream & inputStream);

	bool getNextToken(Token & token);

private:

	std::istream & mInputStream;

	TokenLocation mCurrentLocation;

	ParserRuleList mParserRuleList;


	ParserRulePtr getParserRule(int firstSymbol) const;

	void updateCurrentLocation(int symbol);

	void skipSpaces();

};

#endif // COMPILER_CORE_PARSER_H
