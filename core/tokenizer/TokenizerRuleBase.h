#ifndef COMPILER_CORE_TOKENIZER_TOKENIZER_RULE_BASE_H
#define COMPILER_CORE_TOKENIZER_TOKENIZER_RULE_BASE_H

#include <boost/smart_ptr/shared_ptr.hpp>

#include "core/tokenizer/Token.h"
#include "core/ErrorCodes.h"
#include "core/BufferedInputStream.h"


enum TokenizerRuleState
{
  TRS_Unknown,
  TRS_Intermediate,
  TRS_Finished,
  TRS_Inapropriate
};


enum TokenizerRulePriority
{
  TRR_Default,
  TRR_High
};


class TokenizerRuleBase : private boost::noncopyable
{
public:

  TokenizerRuleBase(TokenType tokenType, TokenizerRulePriority priority = TRR_Default);

  virtual ~TokenizerRuleBase();


  TokenizerRuleState currentState();

  void updateToken(TokenPtr token) const;

  TokenType tokenType() const;

  ErrorCodes lastError() const;

  TokenizerRulePriority priority() const;

  void init(BufferedInputStream & inputStream);

  virtual TokenizerRuleState consumeSymbol() = 0;

  virtual bool firstSymbolFits(int firstSymbol) = 0;


protected:

  BufferedInputStream * mInputStream;

  TokenizerRuleState mCurrentState;
  TokenType mTokenType;
  ErrorCodes mLastError;
  TokenizerRulePriority mPriority;

  virtual void internalInit();

  virtual void internalUpdateToken(TokenPtr token) const;

};


typedef boost::shared_ptr<TokenizerRuleBase> TokenizerRulePtr;

#endif // COMPILER_CORE_TOKENIZER_TOKENIZER_RULE_BASE_H
