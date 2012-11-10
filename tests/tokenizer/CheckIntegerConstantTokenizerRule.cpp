#include "CheckTokenizerRule.h"


#include "core/tokenizer/rules/IntegerConstantTokenizerRule.h"


class CheckIntegerConstantTokenizerRule : public CheckTokenizerRule
{
public:

	IntegerConstantTokenizerRule rule;
};


TEST_F(CheckIntegerConstantTokenizerRule, CheckZeroDecimalValueWithoutSuffix)
{
	const char sample [] = "0";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(sample, result);
}




TEST_F(CheckIntegerConstantTokenizerRule, CheckZeroOctalValueWithoutSuffix)
{
	const char sample [] = "00";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(sample, result);
}



TEST_F(CheckIntegerConstantTokenizerRule, ExpectErrorOnHexadecimalValueWithoutDigitAfterXAndWithoutSuffix)
{
	const char sample [] = "0x";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Inapropriate, rule.consumeSymbol());
}



TEST_F(CheckIntegerConstantTokenizerRule, CheckDecimalNumberWithUnsignedSuffix)
{
	const char sample [] = "5u";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(sample, result);
}


TEST_F(CheckIntegerConstantTokenizerRule, CheckDecimalNumberWithUnsignedAndLongSuffix)
{
	const char sample [] = "5ul";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(sample, result);
}



TEST_F(CheckIntegerConstantTokenizerRule, CheckDecimalNumberWithUnsignedAndLongLongSuffix)
{
	const char sample [] = "5ull";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(sample, result);
}




TEST_F(CheckIntegerConstantTokenizerRule, ExpectErrorOnWrongLongLongSuffix)
{
	const char sample [] = "5Ll";
	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Inapropriate, rule.consumeSymbol());
}
