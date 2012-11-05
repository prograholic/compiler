#ifndef COMPILER_CORE_TOKENIZER_RULES_RELATION_OPERATOR_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_RELATION_OPERATOR_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class RelationOperatorTokenizerRule : public TokenizerRuleBase
{
public:

	RelationOperatorTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();


private:

	enum IS_RelOpsState
	{
		IS_WaitFirstSymbol,
		IS_WaitSecondSymbol
	};

	IS_RelOpsState mInternalState;


	void internalInit();

};

#endif // COMPILER_CORE_TOKENIZER_RULES_RELATION_OPERATOR_TOKENIZER_RULE_H
