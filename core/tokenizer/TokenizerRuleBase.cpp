#include "core/tokenizer/TokenizerRuleBase.h"

TokenizerRuleBase::TokenizerRuleBase(TokenType tokenType, TokenizerRulePriority priority)
  : mInputStream(0),
    mCurrentState(TRS_Unknown),
    mTokenType(tokenType),
    mLastError(EC_NoError),
    mPriority(priority)
{
}

TokenizerRuleBase::~TokenizerRuleBase()
{
}



void TokenizerRuleBase::updateToken(TokenPtr token) const
{
  token->type = mTokenType;

  token->lexeme = StringRef(mInputStream->buffer(),
               mInputStream->currentScopePosition(),
               mInputStream->currentPosition());

  internalUpdateToken(token);
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



void TokenizerRuleBase::init(BufferedInputStream & inputStream)
{
  inputStream.markCurrentScope();

  mInputStream = &inputStream;
  mCurrentState = TRS_Unknown;

  this->internalInit();
}


TokenizerRuleState TokenizerRuleBase::currentState()
{
  return mCurrentState;
}





//////////////////////// Private implementation ////////////////////////



void TokenizerRuleBase::internalInit()
{
}

void TokenizerRuleBase::internalUpdateToken(TokenPtr /* token */) const
{

}
