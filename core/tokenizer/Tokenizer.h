#ifndef COMPILER_CORE_TOKENIZER_TOKENIZER_H
#define COMPILER_CORE_TOKENIZER_TOKENIZER_H

#include "core/tokenizer/TokenizerRulesFacade.h"
#include "core/Error.h"
#include "core/BufferedInputStream.h"

class Tokenizer : private boost::noncopyable
{
public:
  Tokenizer(const TokenizerRulesFacade & tokenizerRules, BufferedInputStream & inputStream);

  bool getNextToken(TokenPtr token);

  Error lastError() const;

private:

  BufferedInputStream & mInputStream;

  TokenizerRulesFacade mTokenizerRules;

  Error mLastError;

  bool returnWithError(ErrorCodes ec);

  bool processOneRule(int symbol, TokenizerRulePtr rule, TokenPtr token);

};

#endif // COMPILER_CORE_TOKENIZER_TOKENIZER_H
