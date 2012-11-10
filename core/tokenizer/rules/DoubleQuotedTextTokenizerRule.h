#ifndef COMPILER_CORE_TOKENIZER_RULES_DOUBLE_QUOTED_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_DOUBLE_QUOTED_TOKENIZER_RULE_H


#include "core/tokenizer/TokenizerRuleBase.h"

class DoubleQuotedTextTokenizerRule : public TokenizerRuleBase
{
public:

	DoubleQuotedTextTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();

private:

	enum InternalState
	{
		IS_WaitFirstDoubleQuote,
		IS_WaitSecondDoubleQuote,
		IS_WaitEscapedSymbol,

		IS_WaitOctalValue1,
		IS_WaitOctalValue2,

		IS_WaitHexValue0,
		IS_WaitHexValue1,

		IS_Finished
	};

	InternalState mInternalState;


	unsigned int mTempForOctalValue;
	unsigned int mTempForHexValue;


	std::string mHolder;

	void consumeMaskedSymbol(int symbol);

	void consumeOctalValue1(int symbol);

	void consumeOctalValue2(int symbol);

	void consumeHexValue0(int symbol);

	void consumeHexValue1(int symbol);



	virtual void internalInit();

	virtual void internalUpdateToken(Token & token) const;
};

#endif // COMPILER_CORE_TOKENIZER_RULES_DOUBLE_QUOTED_TOKENIZER_RULE_H
