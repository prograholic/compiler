#ifndef COMPILER_CORE_BUFFERED_INPUT_STREAM_H
#define COMPILER_CORE_BUFFERED_INPUT_STREAM_H

#include "core/InputStreamBase.h"
#include "core/StreamBuffer.h"

class BufferedInputStream : public InputStreamBase
{
public:
	BufferedInputStream(InputStreamBase & inputStream);

	virtual int peek();

	virtual int next();

	virtual Location currentLocation();


	void markCurrentScope();

	void unwind();

	StreamBufferPtr buffer();

private:

	InputStreamBase & mInputStream;

	StreamBufferPtr mReadedData;

	size_t mCurrentPosition;
	size_t mCurrentScopePosition;


	void readToInternalBuffer();
};

#endif // COMPILER_CORE_BUFFERED_INPUT_STREAM_H
