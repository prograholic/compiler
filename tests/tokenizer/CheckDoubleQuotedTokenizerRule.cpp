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
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

  rule.updateToken(result);

  std::string * advValue = result->advanced_value<std::string>();
  ASSERT_NE(nullPointer, advValue);

  EXPECT_EQ("", *advValue);
}


TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithoutEscapedSymbols)
{
  // unformatted string: "ab"
  const char sample [] = "\"ab\"";
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

  rule.updateToken(result);

  std::string * advValue = result->advanced_value<std::string>();
  ASSERT_NE(nullPointer, advValue);

  EXPECT_EQ("ab", *advValue);
}


TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithEscapedSymbolNewline)
{
  // unformatted string "\n"
  const char sample [] = "\"\\n\"";
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

  rule.updateToken(result);

  std::string * advValue = result->advanced_value<std::string>();
  ASSERT_NE(nullPointer, advValue);

  EXPECT_EQ("\n", *advValue);
}

TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithEscapedSymbolOctal)
{
  // unformatted string "\036"
  const char sample [] = "\"\\036\"";
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

  rule.updateToken(result);

  std::string * advValue = result->advanced_value<std::string>();
  ASSERT_NE(nullPointer, advValue);

  EXPECT_EQ("\036", *advValue);
}


TEST_F(CheckDoubleQuotedTokenizerRule, CheckStringWithEscapedSymbolCStringTerminator)
{
  // unformatted string "\0"
  const char sample [] = "\"\\0\"";
  rule.init(streamFromSample(sample));

  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Intermediate, rule.consumeSymbol());
  ASSERT_EQ(TRS_Finished, rule.consumeSymbol());

  rule.updateToken(result);

  std::string * advValue = result->advanced_value<std::string>();
  ASSERT_NE(nullPointer, advValue);

  ASSERT_EQ(1, advValue->size());
  EXPECT_EQ('\0', (*advValue)[0]);
}
