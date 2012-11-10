#ifndef COMPILER_CORE_TOKENIZER_RULES_PREDEFINED_NAME_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_PREDEFINED_NAME_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"


/**
 * By default all predefined tokens has higher priority, than other tokens
 */
class PredefinedNameTokenizerRule : public TokenizerRuleBase
{
public:
	PredefinedNameTokenizerRule(TokenType tokenType, const std::string & predefinedName);

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();

private:

	std::string mPredefinedName;

	size_t mCurrentSymbolPosition;


	virtual void internalInit();
};

#endif // COMPILER_CORE_TOKENIZER_RULES_PREDEFINED_NAME_TOKENIZER_RULE_H
