#include <gtest/gtest.h>

#include <sstream>

#include <boost/smart_ptr/scoped_ptr.hpp>

#include "core/tokenizer/Tokenizer.h"
#include "core/tokenizer/TokenizerRulesFacade.h"

#include "core/StdInputStreamAdapter.h"
#include "core/BufferedInputStream.h"



#include "CheckTokenizerRule.h"




class CheckTokenizer : public ::testing::Test
{
public:

  void SetUp()
  {
  }


  void TearDown()
  {
  }


  BufferedInputStream & streamFromSample(const std::string & sample)
  {
    mInputStream.reset(new std::istringstream(sample));
    mStdInputStreamAdapter.reset(new StdInputStreamAdapter(mInputStream.get()));
    mBufferedInputStream.reset(new BufferedInputStream(*mStdInputStreamAdapter));

    return *mBufferedInputStream;
  }


  TokenizerRulesFacade tokenizerRules;


private:


  boost::scoped_ptr<std::istringstream> mInputStream;
  boost::scoped_ptr<StdInputStreamAdapter> mStdInputStreamAdapter;
  boost::scoped_ptr<BufferedInputStream> mBufferedInputStream;

};



testing::AssertionResult tokenChecking(TokenPtr t, const std::string & name, size_t line, size_t col, TokenType tokenType)
{
  if (t->lexeme.toString() != name)
  {
    return ::testing::AssertionFailure() << "bad token name [" << t->lexeme.toString() << "], "
                        "expected [" << name << "]";
  }

  if (t->location.line != line)
  {
    return ::testing::AssertionFailure() << "bad token line location [" << t->location.line << "], "
                        "expected [" << line << "]";
  }

  if (t->location.colon != col)
  {
    return ::testing::AssertionFailure() << "bad token colon location [" << t->location.colon << "], "
                        "expected [" << col << "]";
  }

  if (t->type != tokenType)
  {
    return ::testing::AssertionFailure() << "bad token type [" << t->type << "], "
                        "expected [" << tokenType << "]";
  }


  return ::testing::AssertionSuccess();
}




TEST_F(CheckTokenizer, CheckPositionsOfDeclarationIntVariable)
{
  const char sample [] = "int x;";

  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr intToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(intToken));
  EXPECT_TRUE(tokenChecking(intToken, "int", 0, 0, TK_Int));


  TokenPtr xToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(xToken));
  EXPECT_TRUE(tokenChecking(xToken, "x", 0, 4, TK_AlphaNum));

  TokenPtr semicolonToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
  EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 5, TK_Semicolon));

  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}




TEST_F(CheckTokenizer, CheckPositionsOfDeclarationVoidFuncionWithPointerToIntArgument)
{
  const char sample [] = "void func(int * y);";

  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr voidToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(voidToken));
  EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0, TK_Void));


  TokenPtr funcToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(funcToken));
  EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5, TK_AlphaNum));

  TokenPtr openParenToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(openParenToken));
  EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9, TK_OpenParen));

  TokenPtr intToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(intToken));
  EXPECT_TRUE(tokenChecking(intToken, "int", 0, 10, TK_Int));

  TokenPtr starToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(starToken));
  EXPECT_TRUE(tokenChecking(starToken, "*", 0, 14, TK_Star));

  TokenPtr yToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(yToken));
  EXPECT_TRUE(tokenChecking(yToken, "y", 0, 16, TK_AlphaNum));

  TokenPtr closeParenToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(closeParenToken));
  EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 17, TK_CloseParen));

  TokenPtr semicolonToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
  EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 18, TK_Semicolon));


  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}


TEST_F(CheckTokenizer, CheckPositionsOfRealisationOfVoidFunctionWithoutArgumentsAndWithNewLines)
{
  const char sample [] =
      "void func()\n"
      "{\n"
      "}\n";

  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr voidToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(voidToken));
  EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0, TK_Void));


  TokenPtr funcToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(funcToken));
  EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5, TK_AlphaNum));

  TokenPtr openParenToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(openParenToken));
  EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9, TK_OpenParen));

  TokenPtr closeParenToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(closeParenToken));
  EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 10, TK_CloseParen));

  TokenPtr openBraceToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(openBraceToken));
  EXPECT_TRUE(tokenChecking(openBraceToken, "{", 1, 0, TK_OpenBrace));

  TokenPtr closeBraceToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(closeBraceToken));
  EXPECT_TRUE(tokenChecking(closeBraceToken, "}", 2, 0, TK_CloseBrace));

  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}


TEST_F(CheckTokenizer, CheckPositionsOfArrayOfCharDeclaration)
{
  /**
   * unformatted: const char s [] = "abc\" def";
   * value of stringToken must be: [abc" def] - 8 symbols count
   */
  const char sample [] = "const char s [] = \"abc\\\" def\";";
  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr constToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(constToken));
  EXPECT_TRUE(tokenChecking(constToken, "const", 0, 0, TK_Const));

  TokenPtr charToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(charToken));
  EXPECT_TRUE(tokenChecking(charToken, "char", 0, 6, TK_Char));

  TokenPtr sToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(sToken));
  EXPECT_TRUE(tokenChecking(sToken, "s", 0, 11, TK_AlphaNum));

  TokenPtr openBracketToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(openBracketToken));
  EXPECT_TRUE(tokenChecking(openBracketToken, "[", 0, 13, TK_OpenBracket));

  TokenPtr closeBracketToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(closeBracketToken));
  EXPECT_TRUE(tokenChecking(closeBracketToken, "]", 0, 14, TK_CloseBracket));

  TokenPtr assignmentToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(assignmentToken));
  EXPECT_TRUE(tokenChecking(assignmentToken, "=", 0, 16, TK_Assignment));

  TokenPtr stringToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(stringToken));
  EXPECT_TRUE(tokenChecking(stringToken, "\"abc\\\" def\"", 0, 18, TK_DoubleQuotedText));
  std::string * advValue = stringToken->advanced_value<std::string>();
  ASSERT_NE(nullPointer, advValue);
  EXPECT_EQ("abc\" def", *advValue);

  TokenPtr semicolonToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
  EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 29, TK_Semicolon));

  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}



TEST_F(CheckTokenizer, CheckPreIncrement)
{
  const char sample [] = "++x;";
  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr incrementToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(incrementToken));
  EXPECT_TRUE(tokenChecking(incrementToken, "++", 0, 0, TK_Increment));

  TokenPtr xToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(xToken));
  EXPECT_TRUE(tokenChecking(xToken, "x", 0, 2, TK_AlphaNum));

  TokenPtr semicolonToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
  EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 3, TK_Semicolon));

  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}



TEST_F(CheckTokenizer, CheckPreDecrement)
{
  const char sample [] = "--x;";
  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr incrementToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(incrementToken));
  EXPECT_TRUE(tokenChecking(incrementToken, "--", 0, 0, TK_Decrement));

  TokenPtr xToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(xToken));
  EXPECT_TRUE(tokenChecking(xToken, "x", 0, 2, TK_AlphaNum));

  TokenPtr semicolonToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
  EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 3, TK_Semicolon));

  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}


TEST_F(CheckTokenizer, CheckAssignmentAndRelationOperator)
{
  const char sample [] = "if (x == y) z = 5;";
  Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

  TokenPtr ifToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(ifToken));
  EXPECT_TRUE(tokenChecking(ifToken, "if", 0, 0, TK_If));

  TokenPtr openParenToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(openParenToken));
  EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 3, TK_OpenParen));

  TokenPtr xToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(xToken));
  EXPECT_TRUE(tokenChecking(xToken, "x", 0, 4, TK_AlphaNum));

  TokenPtr relationEqualityToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(relationEqualityToken));
  EXPECT_TRUE(tokenChecking(relationEqualityToken, "==", 0, 6, TK_RelationOperator));

  TokenPtr yToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(yToken));
  EXPECT_TRUE(tokenChecking(yToken, "y", 0, 9, TK_AlphaNum));

  TokenPtr closeParenToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(closeParenToken));
  EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 10, TK_CloseParen));

  TokenPtr zToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(zToken));
  EXPECT_TRUE(tokenChecking(zToken, "z", 0, 12, TK_AlphaNum));

  TokenPtr assignmentToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(assignmentToken));
  EXPECT_TRUE(tokenChecking(assignmentToken, "=", 0, 14, TK_Assignment));

  TokenPtr _5Token = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(_5Token));
  EXPECT_TRUE(tokenChecking(_5Token, "5", 0, 16, TK_IntegerConstant));

  TokenPtr semicolonToken = make_token();
  ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
  EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 17, TK_Semicolon));

  TokenPtr unusedToken = make_token();
  EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}
