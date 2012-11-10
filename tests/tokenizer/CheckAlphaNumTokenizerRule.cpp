#include "CheckTokenizerRule.h"

#include "core/tokenizer/rules/AlphaNumTokenizerRule.h"


class CheckAlphaNumTokenizerRule : public CheckTokenizerRule
{
public:


	AlphaNumTokenizerRule rule;
};


TEST_F(CheckAlphaNumTokenizerRule, CheckUnderscoreValues)
{
	const char sample [] = "_x";

	rule.init(streamFromSample(sample), result);

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());


	EXPECT_EQ(sample, result);
}
