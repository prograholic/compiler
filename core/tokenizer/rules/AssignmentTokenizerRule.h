#ifndef COMPILER_CORE_TOKENIZER_RULES_ASSIGNMENT_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_ASSIGNMENT_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class AssignmentTokenizerRule : public TokenizerRuleBase
{
public:
	AssignmentTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();

};

#endif // COMPILER_CORE_TOKENIZER_RULES_ASSIGNMENT_TOKENIZER_RULE_H
