#include "ParserRuleBase.h"

ParserRuleBase::ParserRuleBase(TokenType tokenType)
	: mHolder(0),
	  mInputStream(0),
	  mCurrentState(PRS_Unknown),
	  mTokenType(tokenType),
	  mLastError(EC_NoError)
{
}

ParserRuleBase::~ParserRuleBase()
{
}



void ParserRuleBase::updateTokenTypeForToken(Token & token) const
{
	token.type = mTokenType;
}

TokenType ParserRuleBase::tokenType() const
{
	return mTokenType;
}

ErrorCodes ParserRuleBase::lastError() const
{
	return mLastError;
}



void ParserRuleBase::init(BufferedInputStream & inputStream, std::string & holder)
{
	mHolder = &holder;
	mInputStream = &inputStream;
	mCurrentState = PRS_Unknown;

	inputStream.markCurrentScope();
}


ParserRuleState ParserRuleBase::currentState()
{
	return mCurrentState;
}
