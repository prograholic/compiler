#ifndef COMPILER_CORE_STRING_REF_H
#define COMPILER_CORE_STRING_REF_H

#include <string>

#include "core/StreamBuffer.h"



class StringRef
{
public:
	StringRef();

	explicit StringRef(StreamBufferPtr buffer);

	StringRef(StreamBufferPtr buffer, size_t first);

	StringRef(StreamBufferPtr buffer, size_t first, size_t last);



	StreamBufferPtr buffer() const;

	size_t first() const;

	size_t last() const;



	void advance_front();

	void advance_back();


	bool empty() const;


	std::string toString() const;

private:

	StreamBufferPtr mBuffer;
	size_t mFirst;
	size_t mLast;
};





bool operator != (const StringRef & left, const StringRef & right);


bool operator == (const StringRef & left, const StringRef & right);




#endif // COMPILER_CORE_STRING_REF_H
