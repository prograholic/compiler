#include <gtest/gtest.h>

#include <sstream>

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/scoped_ptr.hpp>

#include "core/Parser.h"

#include "core/ParserRules.h"

class CheckParser : public ::testing::Test
{


public:

	void SetUp()
	{
		parserRuleList.push_back(boost::make_shared<AlphaNumParserRule>());
		parserRuleList.push_back(boost::make_shared<DoubleQuotedTextParserRule>());

		parserRuleList.push_back(boost::make_shared<SemicolonParserRule>());

		parserRuleList.push_back(boost::make_shared<StarParserRule>());

		parserRuleList.push_back(boost::make_shared<AssignmentParserRule>());


		parserRuleList.push_back(boost::make_shared<OpenParenParserRule>());
		parserRuleList.push_back(boost::make_shared<CloseParenParserRule>());

		parserRuleList.push_back(boost::make_shared<OpenBraceParserRule>());
		parserRuleList.push_back(boost::make_shared<CloseBraceParserRule>());

		parserRuleList.push_back(boost::make_shared<OpenBracketParserRule>());
		parserRuleList.push_back(boost::make_shared<CloseBracketParserRule>());
	}


	void TearDown()
	{
		parserRuleList.clear();
	}


	ParserRuleList parserRuleList;
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




TEST_F(CheckParser, CheckPositionsOfDeclarationIntVariable)
{
	const char sample [] = "int x;";

	std::istringstream inputStream(sample);

	Parser parser(parserRuleList, inputStream);

	Token intToken;
	ASSERT_TRUE(parser.getNextToken(intToken));
	EXPECT_TRUE(tokenChecking(intToken, "int", 0, 0, TK_AlphaNum));


	Token xToken;
	ASSERT_TRUE(parser.getNextToken(xToken));
	EXPECT_TRUE(tokenChecking(xToken, "x", 0, 4, TK_AlphaNum));

	Token semicolonToken;
	ASSERT_TRUE(parser.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 5, TK_Semicolon));

	Token unusedToken;
	EXPECT_FALSE(parser.getNextToken(unusedToken));
}




TEST_F(CheckParser, CheckPositionsOfDeclarationVoidFuncionWithPointerToIntArgument)
{
	const char sample [] = "void func(int * y);";
	std::istringstream inputStream(sample);

	Parser parser(parserRuleList, inputStream);

	Token voidToken;
	ASSERT_TRUE(parser.getNextToken(voidToken));
	EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0, TK_AlphaNum));


	Token funcToken;
	ASSERT_TRUE(parser.getNextToken(funcToken));
	EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5, TK_AlphaNum));

	Token openParenToken;
	ASSERT_TRUE(parser.getNextToken(openParenToken));
	EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9, TK_OpenParen));

	Token intToken;
	ASSERT_TRUE(parser.getNextToken(intToken));
	EXPECT_TRUE(tokenChecking(intToken, "int", 0, 10, TK_AlphaNum));

	Token starToken;
	ASSERT_TRUE(parser.getNextToken(starToken));
	EXPECT_TRUE(tokenChecking(starToken, "*", 0, 14, TK_Star));

	Token yToken;
	ASSERT_TRUE(parser.getNextToken(yToken));
	EXPECT_TRUE(tokenChecking(yToken, "y", 0, 16, TK_AlphaNum));

	Token closeParenToken;
	ASSERT_TRUE(parser.getNextToken(closeParenToken));
	EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 17, TK_CloseParen));

	Token semicolonToken;
	ASSERT_TRUE(parser.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 18, TK_Semicolon));


	Token unusedToken;
	EXPECT_FALSE(parser.getNextToken(unusedToken));
}


TEST_F(CheckParser, CheckPositionsOfRealisationOfVoidFunctionWithoutArgumentsAndWithNewLines)
{
	const char sample [] =
			"void func()\n"
			"{\n"
			"}\n";

	std::istringstream inputStream(sample);

	Parser parser(parserRuleList, inputStream);

	Token voidToken;
	ASSERT_TRUE(parser.getNextToken(voidToken));
	EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0, TK_AlphaNum));


	Token funcToken;
	ASSERT_TRUE(parser.getNextToken(funcToken));
	EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5, TK_AlphaNum));

	Token openParenToken;
	ASSERT_TRUE(parser.getNextToken(openParenToken));
	EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9, TK_OpenParen));

	Token closeParenToken;
	ASSERT_TRUE(parser.getNextToken(closeParenToken));
	EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 10, TK_CloseParen));

	Token openBraceToken;
	ASSERT_TRUE(parser.getNextToken(openBraceToken));
	EXPECT_TRUE(tokenChecking(openBraceToken, "{", 1, 0, TK_OpenBrace));

	Token closeBraceToken;
	ASSERT_TRUE(parser.getNextToken(closeBraceToken));
	EXPECT_TRUE(tokenChecking(closeBraceToken, "}", 2, 0, TK_CloseBrace));

	Token unusedToken;
	EXPECT_FALSE(parser.getNextToken(unusedToken));
}


TEST_F(CheckParser, CheckPositionsOfArrayOfCharDeclaration)
{
	/**
	 * unformatted: const char s [] = "abc\" def";
	 * value of stringToken must be: [abc" def] - 8 symbols count
	 */
	const char sample [] = "const char s [] = \"abc\\\" def\";";
	std::istringstream inputStream(sample);

	Parser parser(parserRuleList, inputStream);

	Token constToken;
	ASSERT_TRUE(parser.getNextToken(constToken));
	EXPECT_TRUE(tokenChecking(constToken, "const", 0, 0, TK_AlphaNum));

	Token charToken;
	ASSERT_TRUE(parser.getNextToken(charToken));
	EXPECT_TRUE(tokenChecking(charToken, "char", 0, 6, TK_AlphaNum));

	Token sToken;
	ASSERT_TRUE(parser.getNextToken(sToken));
	EXPECT_TRUE(tokenChecking(sToken, "s", 0, 11, TK_AlphaNum));

	Token openBracketToken;
	ASSERT_TRUE(parser.getNextToken(openBracketToken));
	EXPECT_TRUE(tokenChecking(openBracketToken, "[", 0, 13, TK_OpenBracket));

	Token closeBracketToken;
	ASSERT_TRUE(parser.getNextToken(closeBracketToken));
	EXPECT_TRUE(tokenChecking(closeBracketToken, "]", 0, 14, TK_CloseBracket));

	Token assignmentToken;
	ASSERT_TRUE(parser.getNextToken(assignmentToken));
	EXPECT_TRUE(tokenChecking(assignmentToken, "=", 0, 16, TK_Assignment));

	Token stringToken;
	ASSERT_TRUE(parser.getNextToken(stringToken));
	EXPECT_TRUE(tokenChecking(stringToken, "abc\" def", 0, 18, TK_DoubleQuotedText));

	Token semicolonToken;
	ASSERT_TRUE(parser.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 29, TK_Semicolon));

	Token unusedToken;
	EXPECT_FALSE(parser.getNextToken(unusedToken));
}
