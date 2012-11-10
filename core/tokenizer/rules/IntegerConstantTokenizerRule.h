#ifndef COMPILER_CORE_TOKENIZER_RULES_INTEGER_CONSTANT_TOKENIZER_RULE_H
#define COMPILER_CORE_TOKENIZER_RULES_INTEGER_CONSTANT_TOKENIZER_RULE_H

#include "core/tokenizer/TokenizerRuleBase.h"

class IntegerConstantTokenizerRule : public TokenizerRuleBase
{
public:
	IntegerConstantTokenizerRule();

	virtual bool firstSymbolFits(int firstSymbol);

	virtual TokenizerRuleState consumeSymbol();


private:
	enum InternalState
	{
		IS_WaitFirstSymbol,
		IS_FirstSymbolWasZero,
		IS_DecimalNumber,
		IS_OctalNumber,
		IS_WaitForHexadecimalNumber,
		IS_HexadecimalNumber,

		IS_Suffix
	};

	enum SuffixType
	{
		ST_UnsignedBit = (1 << 0),
		ST_FirstLongBit = (1 << 1),
		ST_SecondLongBit = (1 << 2)
	};


	InternalState mInternalState;
	unsigned int mSuffixType;


	virtual void internalInit();

	void checkOptionalSuffix(const int symbol);



	void onWaitFirstSymbol(const int symbol);

	void onFirstSymbolWasZero(const int symbol);

	void onDecimalNumber(const int symbol);

	void onOctalNumber(const int symbol);

	void onHexadecimalNumber(const int symbol);

};

#endif // COMPILER_CORE_TOKENIZER_RULES_INTEGER_CONSTANT_TOKENIZER_RULE_H
