#include <gtest/gtest.h>

#include <sstream>

#include <boost/smart_ptr/make_shared.hpp>
#include <boost/scoped_ptr.hpp>

#include "core/Parser.h"

#include "core/ParserRules.h"

namespace consts
{
	const char sample000000 [] = "int x;";

	const char sample000001 [] = "void func(int * y);";
}


class CheckParser : public ::testing::Test
{


public:

	void SetUp()
	{
		parserRuleList.push_back(boost::make_shared<AlphaNumParserRule>());
		parserRuleList.push_back(boost::make_shared<SemicolonParserRule>());
	}


	void TearDown()
	{
		parserRuleList.clear();
	}


	ParserRuleList parserRuleList;
};

TEST_F(CheckParser, CheckPositionOfSample000000)
{
	std::istringstream inputStream(consts::sample000000);

	Parser parser(parserRuleList, inputStream);

	{
		Lexeme l;

		ASSERT_TRUE(parser.getNextLexeme(l));

		EXPECT_EQ("int", l.lexeme);
		EXPECT_EQ(0, l.loc.line);
		EXPECT_EQ(0, l.loc.colon);
	}

	{
		Lexeme l;

		ASSERT_TRUE(parser.getNextLexeme(l));

		EXPECT_EQ("x", l.lexeme);
		EXPECT_EQ(0, l.loc.line);
		EXPECT_EQ(4, l.loc.colon);
	}

	{
		Lexeme l;

		ASSERT_TRUE(parser.getNextLexeme(l));

		EXPECT_EQ(";", l.lexeme);
		EXPECT_EQ(0, l.loc.line);
		EXPECT_EQ(5, l.loc.colon);
	}
}
