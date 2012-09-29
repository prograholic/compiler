#include <gtest/gtest.h>

#include <sstream>

#include <boost/smart_ptr/make_shared.hpp>

#include "core/Parser.h"

#include "core/ParserRules.h"

namespace consts
{
	const char sample000000 [] = "int x;";
}


TEST(CheckParser, CheckPositionOfSample000000)
{
	std::istringstream inputStream(consts::sample000000);

	Parser p(inputStream);

	p.addParserRule(boost::make_shared<AlphaNumParserRule>());
	p.addParserRule(boost::make_shared<SemicolonParserRule>());

	{
		Lexeme l;

		ASSERT_TRUE(p.getNextLexeme(l));

		EXPECT_EQ("int", l.lexeme);
		EXPECT_EQ(0, l.loc.line);
		EXPECT_EQ(0, l.loc.colon);
	}


	{
		Lexeme l;

		ASSERT_TRUE(p.getNextLexeme(l));

		EXPECT_EQ("x", l.lexeme);
		EXPECT_EQ(0, l.loc.line);
		EXPECT_EQ(4, l.loc.colon);
	}


	{
		Lexeme l;

		ASSERT_TRUE(p.getNextLexeme(l));

		EXPECT_EQ(";", l.lexeme);
		EXPECT_EQ(0, l.loc.line);
		EXPECT_EQ(5, l.loc.colon);
	}
}
