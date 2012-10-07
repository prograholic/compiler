#ifndef COMPILER_CORE_BUFFERED_INPUT_STREAM_H
#define COMPILER_CORE_BUFFERED_INPUT_STREAM_H

#include <vector>

#include "core/InputStreamBase.h"

class BufferedInputStream : public InputStreamBase
{
public:
	BufferedInputStream(InputStreamBase & inputStream);

	virtual int peek();

	virtual int next();

	virtual Location currentLocation();


	void markCurrentScope();

	void unwind();

private:

	InputStreamBase & mInputStream;

	typedef std::pair<int, Location> BufferEntry;
	typedef std::vector<BufferEntry> BufferEntries;

	BufferEntries mReadedData;

	size_t mCurrentPosition;
	size_t mCurrentScopePosition;


	void readToInternalBuffer();
};

#endif // COMPILER_CORE_BUFFERED_INPUT_STREAM_H
