#ifndef COMPILER_CORE_PARSER_H
#define COMPILER_CORE_PARSER_H

#include "core/ParserRuleBase.h"
#include "core/Error.h"

class Parser : private boost::noncopyable
{
public:
	Parser(const ParserRuleList & parserRuleList, std::istream & inputStream);

	bool getNextToken(Token & token);

	Error lastError() const;

private:

	std::istream & mInputStream;

	TokenLocation mCurrentLocation;

	ParserRuleList mParserRuleList;

	Error mLastError;


	ParserRulePtr getParserRule(int firstSymbol) const;

	void updateCurrentLocation(int symbol);

	void skipSpaces();


	bool returnWithError(ErrorCodes ec);

};

#endif // COMPILER_CORE_PARSER_H
