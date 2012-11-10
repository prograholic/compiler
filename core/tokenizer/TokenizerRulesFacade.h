#ifndef COMPILER_CORE_TOKENIZER_TOKENIZER_RULES_FACADE_H
#define COMPILER_CORE_TOKENIZER_TOKENIZER_RULES_FACADE_H

#include <list>
#include <vector>

#include "core/tokenizer/TokenizerRuleBase.h"


typedef std::list<TokenizerRulePtr> TokenizerRuleList;


class TokenizerRulesFacade
{
public:

	TokenizerRulesFacade();

	TokenizerRuleList getTokenizerRules(int firstSymbol) const;


private:


	typedef std::vector<TokenizerRulePtr> TokenizerRuleHolder;
	TokenizerRuleHolder mTokenizerRuleList;


	void constructRules();

	void constructPredefinedSymbolTokenizers();


	void sortWithPriority();
};

#endif // COMPILER_CORE_TOKENIZER_TOKENIZER_RULES_FACADE_H
