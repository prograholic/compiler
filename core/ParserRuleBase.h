#ifndef COMPILER_CORE_PARSER_RULE_BASE_H
#define COMPILER_CORE_PARSER_RULE_BASE_H

#include <list>

#include <boost/smart_ptr/shared_ptr.hpp>

#include "core/Token.h"
#include "core/ErrorCodes.h"
#include "core/BufferedInputStream.h"


enum ParserRuleState
{
	PRS_Unknown,
	PRS_Intermediate,
	PRS_Finished,
	PRS_Inapropriate
};



class ParserRuleBase : private boost::noncopyable
{
public:

	ParserRuleBase(TokenType tokenType);

	virtual ~ParserRuleBase();


	ParserRuleState currentState();

	void updateTokenTypeForToken(Token & token) const;

	TokenType tokenType() const;

	ErrorCodes lastError() const;

	void init(BufferedInputStream & inputStream, std::string & holder);



	virtual bool firstSymbolFits(int firstSymbol) = 0;

	virtual ParserRuleState consumeSymbol() = 0;

protected:

	std::string * mHolder;
	BufferedInputStream * mInputStream;

	ParserRuleState mCurrentState;
	TokenType mTokenType;
	ErrorCodes mLastError;


	virtual void internalInit();

};


typedef boost::shared_ptr<ParserRuleBase> ParserRulePtr;

typedef std::list<ParserRulePtr> ParserRuleList;

#endif // COMPILER_CORE_PARSER_RULE_BASE_H
