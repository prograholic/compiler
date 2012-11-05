#ifndef COMPILER_CORE_TOKENIZER_RULES_PRE_INCREMENT_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_PRE_INCREMENT_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class PreIncrementTokenizerRule : public TokenizerRuleBase
{
public:
	PreIncrementTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();


private:


	enum IS_PreIncrementState
	{
		IS_WaitFirstPlus,
		IS_WaitSecondPlus
	};

	IS_PreIncrementState mInternalState;

	virtual void internalInit();
};

#endif // COMPILER_CORE_TOKENIZER_RULES_PRE_INCREMENT_TOKENIZER_RULE_H
