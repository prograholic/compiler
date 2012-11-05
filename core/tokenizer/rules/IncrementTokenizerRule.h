#ifndef COMPILER_CORE_TOKENIZER_RULES_INCREMENT_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_INCREMENT_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class IncrementTokenizerRule : public TokenizerRuleBase
{
public:
	IncrementTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();


private:


	enum IS_IncrementState
	{
		IS_WaitFirstPlus,
		IS_WaitSecondPlus
	};

	IS_IncrementState mInternalState;

	virtual void internalInit();
};

#endif // COMPILER_CORE_TOKENIZER_RULES_INCREMENT_TOKENIZER_RULE_H
