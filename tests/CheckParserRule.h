#ifndef COMPILER_CORE_CHECK_PARSER_RULE_H
#define COMPILER_CORE_CHECK_PARSER_RULE_H

#include <gtest/gtest.h>



#include "core/ParserRules.h"
#include "core/StdInputStreamAdapter.h"
#include "core/BufferedInputStream.h"


class CheckParserRule : public ::testing::Test
{
public:

	CheckParserRule()
		: ::testing::Test(),
		  stdInputStreamAdapter(0),
		  bufferedInputStream(stdInputStreamAdapter)
	{
	}



	virtual void SetUp()
	{
		result.clear();
	}


	StdInputStreamAdapter stdInputStreamAdapter;
	BufferedInputStream bufferedInputStream;

	std::string result;

};



#endif // COMPILER_CORE_CHECK_PARSER_RULE_H
