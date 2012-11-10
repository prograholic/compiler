#include "CheckTokenizerRule.h"

#include "core/tokenizer/rules/RelationOperatorTokenizerRule.h"

class CheckRelationOperatorParserRule : public CheckTokenizerRule
{
public:

	RelationOperatorTokenizerRule rule;
};



TEST_F(CheckRelationOperatorParserRule, CheckEquality)
{
	const char sample [] = "==";
	rule.init(streamFromSample(sample));

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	rule.updateToken(result);

	EXPECT_EQ("==", result.lexeme.toString());
}


TEST_F(CheckRelationOperatorParserRule, CheckInequality)
{
	const char sample [] = "!=";
	rule.init(streamFromSample(sample));

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	rule.updateToken(result);

	EXPECT_EQ("!=", result.lexeme.toString());
}

TEST_F(CheckRelationOperatorParserRule, CheckGreater)
{
	const char sample [] = ">";
	rule.init(streamFromSample(sample));

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	rule.updateToken(result);

	EXPECT_EQ(">", result.lexeme.toString());
}

TEST_F(CheckRelationOperatorParserRule, CheckLess)
{
	const char sample [] = "<";
	rule.init(streamFromSample(sample));

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	rule.updateToken(result);

	EXPECT_EQ("<", result.lexeme.toString());
}


TEST_F(CheckRelationOperatorParserRule, CheckGreaterOrEqual)
{
	const char sample [] = ">=";
	rule.init(streamFromSample(sample));

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	rule.updateToken(result);

	EXPECT_EQ(">=", result.lexeme.toString());
}

TEST_F(CheckRelationOperatorParserRule, CheckLessOrEqual)
{
	const char sample [] = "<=";
	rule.init(streamFromSample(sample));

	ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
	ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

	rule.updateToken(result);

	EXPECT_EQ("<=", result.lexeme.toString());
}
