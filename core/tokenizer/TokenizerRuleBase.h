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



class TokenizerRuleBase : private boost::noncopyable
{
public:

	TokenizerRuleBase(TokenType tokenType);

	virtual ~TokenizerRuleBase();


	TokenizerRuleState currentState();

	void updateTokenTypeForToken(Token & token) const;

	TokenType tokenType() const;

	ErrorCodes lastError() const;

	void init(BufferedInputStream & inputStream, std::string & holder);



	virtual bool firstSymbolFits(int firstSymbol) = 0;

	virtual TokenizerRuleState consumeSymbol() = 0;

protected:

	std::string * mHolder;
	BufferedInputStream * mInputStream;

	TokenizerRuleState mCurrentState;
	TokenType mTokenType;
	ErrorCodes mLastError;


	virtual void internalInit();

};


typedef boost::shared_ptr<TokenizerRuleBase> TokenizerRulePtr;

#endif // COMPILER_CORE_TOKENIZER_TOKENIZER_RULE_BASE_H
