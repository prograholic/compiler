#ifndef COMPILER_CORE_INPUT_STREAM_BASE_H
#define COMPILER_CORE_INPUT_STREAM_BASE_H

#include <boost/noncopyable.hpp>

#include "core/Location.h"


class InputStreamBase : private boost::noncopyable
{
public:
	InputStreamBase();

	virtual ~InputStreamBase();

	enum
	{
		EndOfFile = -1
	};


	/// get symbol from stream without extracting
	virtual int peek() = 0;

	/// Extract next symbol from stream
	virtual int next() = 0;

	virtual Location currentLocation() = 0;

	void skipSpaces();

private:

};

#endif // INPUTSTREAMBASE_H
