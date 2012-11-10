#include "CheckTokenizerRule.h"

#include "core/tokenizer/rules/DoubleQuotedTextTokenizerRule.h"


class CheckDoubleQuotedTokenizerRule : public CheckTokenizerRule
{
public:

	DoubleQuotedTextTokenizerRule rule;

};


TEST_F(CheckDoubleQuotedTokenizerRule, CheckEmptyString)
{
	// unformatted string: ""
	const char sample [] = "\"\"";
	rule.init(streamFromSample(sample), result);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("", result);
}


TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithoutEscapedSymbols)
{
	// unformatted string: "ab"
	const char sample [] = "\"ab\"";
	rule.init(streamFromSample(sample), result);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("ab", result);
}


TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithEscapedSymbolNewline)
{
	// unformatted string "\n"
	const char sample [] = "\"\\n\"";
	rule.init(streamFromSample(sample), result);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("\n", result);
}

TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithEscapedSymbolOctal)
{
	// unformatted string "\036"
	const char sample [] = "\"\\036\"";
	rule.init(streamFromSample(sample), result);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("\036", result);
}


TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithEscapedSymbolCStringTerminator)
{
	// unformatted string "\0"
	const char sample [] = "\"\\0\"";
	rule.init(streamFromSample(sample), result);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	ASSERT_EQ(1, result.size());
	EXPECT_EQ('\0', result[0]);
}
