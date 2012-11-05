#include "CheckTokenizerRule.h"

#include "core/tokenizer/rules/RelationOperatorTokenizerRule.h"

class CheckRelationOperatorParserRule : public CheckTokenizerRule
{
public:

	virtual void SetUp()
	{
		CheckTokenizerRule::SetUp();

		rule.init(bufferedInputStream, result);
	}


	RelationOperatorTokenizerRule rule;
};



TEST_F(CheckRelationOperatorParserRule, CheckEquality)
{
	const char sample [] = "==";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("==", result);
}


TEST_F(CheckRelationOperatorParserRule, CheckInequality)
{
	const char sample [] = "!=";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("!=", result);
}

TEST_F(CheckRelationOperatorParserRule, CheckGreater)
{
	const char sample [] = ">";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(">", result);
}

TEST_F(CheckRelationOperatorParserRule, CheckLess)
{
	const char sample [] = "<";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("<", result);
}


TEST_F(CheckRelationOperatorParserRule, CheckGreaterOrEqual)
{
	const char sample [] = ">=";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(">=", result);
}

TEST_F(CheckRelationOperatorParserRule, CheckLessOrEqual)
{
	const char sample [] = "<=";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(TRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(TRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("<=", result);
}
