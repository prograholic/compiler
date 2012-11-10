#include "core/tokenizer/TokenizerRuleBase.h"

TokenizerRuleBase::TokenizerRuleBase(TokenType tokenType, TokenizerRulePriority priority)
	: mHolder(0),
	  mInputStream(0),
	  mCurrentState(TRS_Unknown),
	  mTokenType(tokenType),
	  mLastError(EC_NoError),
	  mPriority(priority)
{
}

TokenizerRuleBase::~TokenizerRuleBase()
{
}



void TokenizerRuleBase::updateTokenTypeForToken(Token & token) const
{
	token.type = mTokenType;
}

TokenType TokenizerRuleBase::tokenType() const
{
	return mTokenType;
}

ErrorCodes TokenizerRuleBase::lastError() const
{
	return mLastError;
}


TokenizerRulePriority TokenizerRuleBase::priority() const
{
	return mPriority;
}



void TokenizerRuleBase::init(BufferedInputStream & inputStream, std::string & holder)
{
	mHolder = &holder;
	mInputStream = &inputStream;
	mCurrentState = TRS_Unknown;

	inputStream.markCurrentScope();

	this->internalInit();
}


TokenizerRuleState TokenizerRuleBase::currentState()
{
	return mCurrentState;
}





//////////////////////// Private implementation ////////////////////////



void TokenizerRuleBase::internalInit()
{}
