#ifndef COMPILER_CORE_PARSER_RULE_BASE_H
#define COMPILER_CORE_PARSER_RULE_BASE_H

#include <list>

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "core/Token.h"



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

#endif // COMPILER_CORE_PARSER_RULE_BASE_H
