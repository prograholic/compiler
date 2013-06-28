#include "CheckTokenizerRule.h"

#include "core/tokenizer/rules/PredefinedNameTokenizerRule.h"


class CheckPredefinedNameTokenizerRule : public CheckTokenizerRule
{
public:

  virtual void SetUp()
  {
    CheckTokenizerRule::SetUp();
  }
};


TEST_F(CheckPredefinedNameTokenizerRule, CheckPositiveScenario)
{
  const char sample [] = "if";

  PredefinedNameTokenizerRule rule(TK_If, "if");
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

  rule.updateToken(result);

  EXPECT_EQ("if", result->lexeme.toString());
}




TEST_F(CheckPredefinedNameTokenizerRule, CheckNegativeScenario)
{
  const char sample [] = "if";

  PredefinedNameTokenizerRule rule(TK_Return, "return");
  rule.init(streamFromSample(sample));

  EXPECT_EQ(TRS_Inapropriate, rule.consumeSymbol());
}


TEST_F(CheckPredefinedNameTokenizerRule, CheckNegativeScenarioWithShortString)
{
  const char sample [] = "ret";

  PredefinedNameTokenizerRule rule(TK_Return, "return");
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  EXPECT_EQ(TRS_Inapropriate, rule.consumeSymbol());
}
