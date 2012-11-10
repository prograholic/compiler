#include <gtest/gtest.h>

#include <sstream>

#include <boost/smart_ptr/scoped_ptr.hpp>

#include "core/tokenizer/Tokenizer.h"
#include "core/tokenizer/TokenizerRulesFacade.h"

#include "core/StdInputStreamAdapter.h"
#include "core/BufferedInputStream.h"




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



testing::AssertionResult tokenChecking(const Token & t, const std::string & name, size_t line, size_t col, TokenType tokenType)
{
	if (t.lexeme != name)
	{
		return ::testing::AssertionFailure() << "bad token name [" << t.lexeme << "], "
												"expected [" << name << "]";
	}

	if (t.location.line != line)
	{
		return ::testing::AssertionFailure() << "bad token line location [" << t.location.line << "], "
												"expected [" << line << "]";
	}

	if (t.location.colon != col)
	{
		return ::testing::AssertionFailure() << "bad token colon location [" << t.location.colon << "], "
												"expected [" << col << "]";
	}

	if (t.type != tokenType)
	{
		return ::testing::AssertionFailure() << "bad token type [" << t.type << "], "
												"expected [" << tokenType << "]";
	}


	return ::testing::AssertionSuccess();
}




TEST_F(CheckTokenizer, CheckPositionsOfDeclarationIntVariable)
{
	const char sample [] = "int x;";

	Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

	Token intToken;
	ASSERT_TRUE(tokenizer.getNextToken(intToken));
	EXPECT_TRUE(tokenChecking(intToken, "int", 0, 0, TK_Int));


	Token xToken;
	ASSERT_TRUE(tokenizer.getNextToken(xToken));
	EXPECT_TRUE(tokenChecking(xToken, "x", 0, 4, TK_AlphaNum));

	Token semicolonToken;
	ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 5, TK_Semicolon));

	Token unusedToken;
	EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}




TEST_F(CheckTokenizer, CheckPositionsOfDeclarationVoidFuncionWithPointerToIntArgument)
{
	const char sample [] = "void func(int * y);";

	Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

	Token voidToken;
	ASSERT_TRUE(tokenizer.getNextToken(voidToken));
	EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0, TK_Void));


	Token funcToken;
	ASSERT_TRUE(tokenizer.getNextToken(funcToken));
	EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5, TK_AlphaNum));

	Token openParenToken;
	ASSERT_TRUE(tokenizer.getNextToken(openParenToken));
	EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9, TK_OpenParen));

	Token intToken;
	ASSERT_TRUE(tokenizer.getNextToken(intToken));
	EXPECT_TRUE(tokenChecking(intToken, "int", 0, 10, TK_Int));

	Token starToken;
	ASSERT_TRUE(tokenizer.getNextToken(starToken));
	EXPECT_TRUE(tokenChecking(starToken, "*", 0, 14, TK_Star));

	Token yToken;
	ASSERT_TRUE(tokenizer.getNextToken(yToken));
	EXPECT_TRUE(tokenChecking(yToken, "y", 0, 16, TK_AlphaNum));

	Token closeParenToken;
	ASSERT_TRUE(tokenizer.getNextToken(closeParenToken));
	EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 17, TK_CloseParen));

	Token semicolonToken;
	ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 18, TK_Semicolon));


	Token unusedToken;
	EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}


TEST_F(CheckTokenizer, CheckPositionsOfRealisationOfVoidFunctionWithoutArgumentsAndWithNewLines)
{
	const char sample [] =
			"void func()\n"
			"{\n"
			"}\n";

	Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

	Token voidToken;
	ASSERT_TRUE(tokenizer.getNextToken(voidToken));
	EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0, TK_Void));


	Token funcToken;
	ASSERT_TRUE(tokenizer.getNextToken(funcToken));
	EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5, TK_AlphaNum));

	Token openParenToken;
	ASSERT_TRUE(tokenizer.getNextToken(openParenToken));
	EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9, TK_OpenParen));

	Token closeParenToken;
	ASSERT_TRUE(tokenizer.getNextToken(closeParenToken));
	EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 10, TK_CloseParen));

	Token openBraceToken;
	ASSERT_TRUE(tokenizer.getNextToken(openBraceToken));
	EXPECT_TRUE(tokenChecking(openBraceToken, "{", 1, 0, TK_OpenBrace));

	Token closeBraceToken;
	ASSERT_TRUE(tokenizer.getNextToken(closeBraceToken));
	EXPECT_TRUE(tokenChecking(closeBraceToken, "}", 2, 0, TK_CloseBrace));

	Token unusedToken;
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

	Token constToken;
	ASSERT_TRUE(tokenizer.getNextToken(constToken));
	EXPECT_TRUE(tokenChecking(constToken, "const", 0, 0, TK_Const));

	Token charToken;
	ASSERT_TRUE(tokenizer.getNextToken(charToken));
	EXPECT_TRUE(tokenChecking(charToken, "char", 0, 6, TK_Char));

	Token sToken;
	ASSERT_TRUE(tokenizer.getNextToken(sToken));
	EXPECT_TRUE(tokenChecking(sToken, "s", 0, 11, TK_AlphaNum));

	Token openBracketToken;
	ASSERT_TRUE(tokenizer.getNextToken(openBracketToken));
	EXPECT_TRUE(tokenChecking(openBracketToken, "[", 0, 13, TK_OpenBracket));

	Token closeBracketToken;
	ASSERT_TRUE(tokenizer.getNextToken(closeBracketToken));
	EXPECT_TRUE(tokenChecking(closeBracketToken, "]", 0, 14, TK_CloseBracket));

	Token assignmentToken;
	ASSERT_TRUE(tokenizer.getNextToken(assignmentToken));
	EXPECT_TRUE(tokenChecking(assignmentToken, "=", 0, 16, TK_Assignment));

	Token stringToken;
	ASSERT_TRUE(tokenizer.getNextToken(stringToken));
	EXPECT_TRUE(tokenChecking(stringToken, "abc\" def", 0, 18, TK_DoubleQuotedText));

	Token semicolonToken;
	ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 29, TK_Semicolon));

	Token unusedToken;
	EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}



TEST_F(CheckTokenizer, CheckPreIncrement)
{
	const char sample [] = "++x;";
	Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

	Token incrementToken;
	ASSERT_TRUE(tokenizer.getNextToken(incrementToken));
	EXPECT_TRUE(tokenChecking(incrementToken, "++", 0, 0, TK_Increment));

	Token xToken;
	ASSERT_TRUE(tokenizer.getNextToken(xToken));
	EXPECT_TRUE(tokenChecking(xToken, "x", 0, 2, TK_AlphaNum));

	Token semicolonToken;
	ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 3, TK_Semicolon));

	Token unusedToken;
	EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}


TEST_F(CheckTokenizer, CheckAssignmentAndRelationOperator)
{
	const char sample [] = "if (x == y) z = 5;";
	Tokenizer tokenizer(tokenizerRules, streamFromSample(sample));

	Token ifToken;
	ASSERT_TRUE(tokenizer.getNextToken(ifToken));
	EXPECT_TRUE(tokenChecking(ifToken, "if", 0, 0, TK_If));

	Token openParenToken;
	ASSERT_TRUE(tokenizer.getNextToken(openParenToken));
	EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 3, TK_OpenParen));

	Token xToken;
	ASSERT_TRUE(tokenizer.getNextToken(xToken));
	EXPECT_TRUE(tokenChecking(xToken, "x", 0, 4, TK_AlphaNum));

	Token relationEqualityToken;
	ASSERT_TRUE(tokenizer.getNextToken(relationEqualityToken));
	EXPECT_TRUE(tokenChecking(relationEqualityToken, "==", 0, 6, TK_RelationOperator));

	Token yToken;
	ASSERT_TRUE(tokenizer.getNextToken(yToken));
	EXPECT_TRUE(tokenChecking(yToken, "y", 0, 9, TK_AlphaNum));

	Token closeParenToken;
	ASSERT_TRUE(tokenizer.getNextToken(closeParenToken));
	EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 10, TK_CloseParen));

	Token zToken;
	ASSERT_TRUE(tokenizer.getNextToken(zToken));
	EXPECT_TRUE(tokenChecking(zToken, "z", 0, 12, TK_AlphaNum));

	Token assignmentToken;
	ASSERT_TRUE(tokenizer.getNextToken(assignmentToken));
	EXPECT_TRUE(tokenChecking(assignmentToken, "=", 0, 14, TK_Assignment));

	Token _5Token;
	ASSERT_TRUE(tokenizer.getNextToken(_5Token));
	EXPECT_TRUE(tokenChecking(_5Token, "5", 0, 16, TK_IntegerConstant));

	Token semicolonToken;
	ASSERT_TRUE(tokenizer.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 17, TK_Semicolon));

	Token unusedToken;
	EXPECT_FALSE(tokenizer.getNextToken(unusedToken));
}
