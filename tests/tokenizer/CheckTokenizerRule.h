#ifndef COMPILER_CORE_CHECK_TOKENIZER_RULE_H
#define COMPILER_CORE_CHECK_TOKENIZER_RULE_H

#include <gtest/gtest.h>

#include <boost/smart_ptr/scoped_ptr.hpp>

#include "core/StdInputStreamAdapter.h"
#include "core/BufferedInputStream.h"


class CheckTokenizerRule : public ::testing::Test
{
public:

	virtual void SetUp()
	{
		result.clear();
	}


	BufferedInputStream & streamFromSample(const std::string & sample)
	{
		mInputStream.reset(new std::istringstream(sample));
		mStdInputStreamAdapter.reset(new StdInputStreamAdapter(mInputStream.get()));
		mBufferedInputStream.reset(new BufferedInputStream(*mStdInputStreamAdapter));

		return *mBufferedInputStream;
	}

	std::string result;

private:


	boost::scoped_ptr<std::istringstream> mInputStream;
	boost::scoped_ptr<StdInputStreamAdapter> mStdInputStreamAdapter;
	boost::scoped_ptr<BufferedInputStream> mBufferedInputStream;

};



#endif // COMPILER_CORE_CHECK_PARSER_RULE_H
