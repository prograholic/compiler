#ifndef COMPILER_CORE_TOKENIZER_RULES_ALPHA_NUM_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_ALPHA_NUM_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class AlphaNumTokenizerRule : public TokenizerRuleBase
{
public:

	AlphaNumTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();

private:

	bool mIsEmpty;


	void internalInit();
};

#endif // COMPILER_CORE_TOKENIZER_RULES_ALPHA_NUM_TOKENIZER_RULE_H
