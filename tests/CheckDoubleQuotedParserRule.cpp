#include <gtest/gtest.h>

#include "core/ParserRules.h"


class CheckDoubleQuotedParserRule : public ::testing::Test
{
public:


	DoubleQuotedTextParserRule rule;

	std::string result;

	virtual void SetUp()
	{
		result.clear();
		rule.init(result);
	}
};

TEST_F(CheckDoubleQuotedParserRule, CheckEmptyString)
{
	// unformatted string: ""
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\"'));
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol('\"'));

	EXPECT_EQ("", result);
}


TEST_F(CheckDoubleQuotedParserRule, CheckStringWithoutEscapedSymbols)
{
	// unformatted string: "ab"
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\"'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('a'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('b'));
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol('\"'));

	EXPECT_EQ("ab", result);
}


TEST_F(CheckDoubleQuotedParserRule, CheckStringWithEscapedSymbolNewline)
{
	// unformatted string "\n"
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\"'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\\'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('n'));
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol('\"'));

	EXPECT_EQ("\n", result);
}

TEST_F(CheckDoubleQuotedParserRule, CheckStringWithEscapedSymbolOctal)
{
	// unformatted string "\036"
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\"'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\\'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('0'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('3'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('6'));
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol('\"'));

	EXPECT_EQ("\036", result);
}


TEST_F(CheckDoubleQuotedParserRule, CheckStringWithEscapedSymbolCStringTerminator)
{
	// unformatted string "\0"
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\"'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('\\'));
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol('0'));
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol('\"'));

	ASSERT_EQ(1, result.size());
	EXPECT_EQ('\0', result[0]);
}
