#include "CheckParserRule.h"



class CheckDoubleQuotedParserRule : public CheckParserRule
{
public:


	virtual void SetUp()
	{
		CheckParserRule::SetUp();

		rule.init(bufferedInputStream, result);
	}


	DoubleQuotedTextParserRule rule;

};


TEST_F(CheckDoubleQuotedParserRule, CheckEmptyString)
{
	// unformatted string: ""
	const char sample [] = "\"\"";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("", result);
}


TEST_F(CheckDoubleQuotedParserRule, CheckStringWithoutEscapedSymbols)
{
	// unformatted string: "ab"
	const char sample [] = "\"ab\"";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("ab", result);
}


TEST_F(CheckDoubleQuotedParserRule, CheckStringWithEscapedSymbolNewline)
{
	// unformatted string "\n"
	const char sample [] = "\"\\n\"";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("\n", result);
}

TEST_F(CheckDoubleQuotedParserRule, CheckStringWithEscapedSymbolOctal)
{
	// unformatted string "\036"
	const char sample [] = "\"\\036\"";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("\036", result);
}


TEST_F(CheckDoubleQuotedParserRule, CheckStringWithEscapedSymbolCStringTerminator)
{
	// unformatted string "\0"
	const char sample [] = "\"\\0\"";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	ASSERT_EQ(1, result.size());
	EXPECT_EQ('\0', result[0]);
}
