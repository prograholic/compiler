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
		parserRuleList.push_back(boost::make_shared<SemicolonParserRule>());
		parserRuleList.push_back(boost::make_shared<OpenParenParserRule>());
		parserRuleList.push_back(boost::make_shared<CloseParenParserRule>());
		parserRuleList.push_back(boost::make_shared<StarParserRule>());
	}


	void TearDown()
	{
		parserRuleList.clear();
	}


	ParserRuleList parserRuleList;
};



testing::AssertionResult tokenChecking(const Token & t, const std::string & name, size_t line, size_t col)
{
	if (t.lexeme != name)
	{
		return ::testing::AssertionFailure() << "bad token name [" << t.lexeme << "], "
												"expected [" << name << "]";
	}

	if (t.loc.line != line)
	{
		return ::testing::AssertionFailure() << "bad token line location [" << t.loc.line << "], "
												"expected [" << line << "]";
	}

	if (t.loc.colon != col)
	{
		return ::testing::AssertionFailure() << "bad token colon location [" << t.loc.colon << "], "
												"expected [" << col << "]";
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
	EXPECT_TRUE(tokenChecking(intToken, "int", 0, 0));


	Token xToken;
	ASSERT_TRUE(parser.getNextToken(xToken));
	EXPECT_TRUE(tokenChecking(xToken, "x", 0, 4));

	Token semicolonToken;
	ASSERT_TRUE(parser.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 5));

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
	EXPECT_TRUE(tokenChecking(voidToken, "void", 0, 0));


	Token funcToken;
	ASSERT_TRUE(parser.getNextToken(funcToken));
	EXPECT_TRUE(tokenChecking(funcToken, "func", 0, 5));

	Token openParenToken;
	ASSERT_TRUE(parser.getNextToken(openParenToken));
	EXPECT_TRUE(tokenChecking(openParenToken, "(", 0, 9));

	Token intToken;
	ASSERT_TRUE(parser.getNextToken(intToken));
	EXPECT_TRUE(tokenChecking(intToken, "int", 0, 10));

	Token starToken;
	ASSERT_TRUE(parser.getNextToken(starToken));
	EXPECT_TRUE(tokenChecking(starToken, "*", 0, 14));

	Token yToken;
	ASSERT_TRUE(parser.getNextToken(yToken));
	EXPECT_TRUE(tokenChecking(yToken, "y", 0, 16));

	Token closeParenToken;
	ASSERT_TRUE(parser.getNextToken(closeParenToken));
	EXPECT_TRUE(tokenChecking(closeParenToken, ")", 0, 17));

	Token semicolonToken;
	ASSERT_TRUE(parser.getNextToken(semicolonToken));
	EXPECT_TRUE(tokenChecking(semicolonToken, ";", 0, 18));


	Token unusedToken;
	EXPECT_FALSE(parser.getNextToken(unusedToken));
}
