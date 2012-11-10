#ifndef COMPILER_CORE_TOKENIZER_RULES_INCREMENT_DECREMENT_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_INCREMENT_DECREMENT_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class IncrementDecrementTokenizerRule : public TokenizerRuleBase
{
public:
	IncrementDecrementTokenizerRule(int requiredSymbol);

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();


private:


	enum IS_IncrementDecrementState
	{
		IS_WaitFirstSymbol,
		IS_WaitSecondSymbol
	};

	IS_IncrementDecrementState mInternalState;

	const int mRequiredSymbol;

	virtual void internalInit();
};

#endif // COMPILER_CORE_TOKENIZER_RULES_INCREMENT_DECREMENT_TOKENIZER_RULE_H
