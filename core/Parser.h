#ifndef COMPILER_CORE_PARSER_H
#define COMPILER_CORE_PARSER_H

#include "core/ParserRuleBase.h"
#include "core/Error.h"
#include "core/BufferedInputStream.h"

class Parser : private boost::noncopyable
{
public:
	Parser(const ParserRuleList & parserRuleList, BufferedInputStream & inputStream);

	bool getNextToken(Token & token);

	Error lastError() const;

private:

	BufferedInputStream & mInputStream;

	ParserRuleList mParserRuleList;

	Error mLastError;


	ParserRulePtr getParserRule(int firstSymbol) const;

	bool returnWithError(ErrorCodes ec);

};

#endif // COMPILER_CORE_PARSER_H
