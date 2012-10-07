#include <gtest/gtest.h>

#include <sstream>



#include "core/ASTBuilder.h"
#include "core/ParserRules.h"
#include "core/StdInputStreamAdapter.h"
#include "core/BufferedInputStream.h"


class CheckASTBuilder : public ::testing::Test
{
public:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};



TEST_F(CheckASTBuilder, CheckVariableDeclaration)
{
	const char sample [] = "int x;";

	std::istringstream inputStream(sample);
	StdInputStreamAdapter stdInputStreamAdapter(&inputStream);
	BufferedInputStream bufferetInputStream(stdInputStreamAdapter);

	Parser parser(getParserRuleList(), bufferetInputStream);

	ASTBuilder astBuilder(parser);
}
