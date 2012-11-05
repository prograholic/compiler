#ifndef COMPILER_CORE_TOKENIZER_TOKENIZER_RULES_FACADE_H
#define COMPILER_CORE_TOKENIZER_TOKENIZER_RULES_FACADE_H

#include <list>

#include "core/tokenizer/TokenizerRuleBase.h"


class TokenizerRulesFacade
{
public:

	TokenizerRulesFacade();

	TokenizerRulePtr getTokenizerRule(int firstSymbol) const;


private:
	typedef std::list<TokenizerRulePtr> TokenizerRuleList;


	TokenizerRuleList mTokenizerRuleList;


};

#endif // COMPILER_CORE_TOKENIZER_TOKENIZER_RULES_FACADE_H
