#include "ParserRuleBase.h"

ParserRuleBase::ParserRuleBase(TokenType tokenType)
	: mHolder(0),
	  mCurrentState(PRS_Unknown),
	  mTokenType(tokenType)
{
}

ParserRuleBase::~ParserRuleBase()
{
}



void ParserRuleBase::setTokenType(Token & token)
{
	token.type = mTokenType;
}

TokenType ParserRuleBase::tokenType() const
{

}


void ParserRuleBase::init(std::string & holder)
{
	mHolder = &holder;
	mCurrentState = PRS_Unknown;
}


ParserRuleState ParserRuleBase::currentState()
{
	return mCurrentState;
}
