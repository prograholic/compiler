#include "CheckParserRule.h"


class CheckRelationOperatorParserRule : public CheckParserRule
{
public:

	virtual void SetUp()
	{
		CheckParserRule::SetUp();

		rule.init(bufferedInputStream, result);
	}


	RelationOperatorParserRule rule;
};



TEST_F(CheckRelationOperatorParserRule, CheckEquality)
{
	const char sample [] = "==";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("==", result);
}


TEST_F(CheckRelationOperatorParserRule, CheckInequality)
{
	const char sample [] = "!=";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("!=", result);
}

TEST_F(CheckRelationOperatorParserRule, CheckGreater)
{
	const char sample [] = ">";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(">", result);
}

TEST_F(CheckRelationOperatorParserRule, CheckLess)
{
	const char sample [] = "<";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("<", result);
}


TEST_F(CheckRelationOperatorParserRule, CheckGreaterOrEqual)
{
	const char sample [] = ">=";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ(">=", result);
}

TEST_F(CheckRelationOperatorParserRule, CheckLessOrEqual)
{
	const char sample [] = "<=";
	std::istringstream inputStream(sample);
	stdInputStreamAdapter.updateInputStream(inputStream);

	EXPECT_EQ(PRS_Intermediate, rule.consumeSymbol());
	EXPECT_EQ(PRS_Finished, rule.consumeSymbol());

	EXPECT_EQ("<=", result);
}
