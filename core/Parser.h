#ifndef COMPILER_CORE_PARSER_H
#define COMPILER_CORE_PARSER_H


#include "core/ParserRuleBase.h"

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
