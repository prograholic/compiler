#include "StringRef.h"

#include <boost/assert.hpp>

StringRef::StringRef()
	: mBuffer(),
	  mFirst(0),
	  mLast(0)
{

}

StringRef::StringRef(StreamBufferPtr buffer)
	: mBuffer(buffer),
	  mFirst(0),
	  mLast(0)
{
}

StringRef::StringRef(StreamBufferPtr buffer, size_t first)
	: mBuffer(buffer),
	  mFirst(first),
	  mLast(first)
{
	BOOST_ASSERT(mBuffer->size() >= mLast);
}

StringRef::StringRef(StreamBufferPtr buffer, size_t first, size_t last)
	: mBuffer(buffer),
	  mFirst(first),
	  mLast(last)
{
	BOOST_ASSERT(mLast >= mFirst);
	BOOST_ASSERT(mBuffer->size() >= mLast);
}





StreamBufferPtr StringRef::buffer() const
{
	return mBuffer;
}

size_t StringRef::first() const
{
	return mFirst;
}

size_t StringRef::last() const
{
	return mLast;
}



void StringRef::advance_front()
{
	++mFirst;

	BOOST_ASSERT(mFirst <= mLast);
}

void StringRef::advance_back()
{
	++mLast;

	BOOST_ASSERT(mLast < mBuffer->size());
}


bool StringRef::empty() const
{
	return !mBuffer.get() || (mFirst == mLast);
}


std::string StringRef::toString() const
{
	if (StreamBuffer * buff = mBuffer.get())
	{
		return std::string(&buff->symbol(mFirst), &buff->symbol(mLast));
	}

	return std::string();
}





bool operator == (const StringRef & left, const StringRef & right)
{
	if (left.buffer().get() != right.buffer().get())
	{
		return false;
	}

	if (left.first() != right.first())
	{
		return false;
	}

	if (left.last() != right.last())
	{
		return false;
	}

	return true;
}


bool operator != (const StringRef & left, const StringRef & right)
{
	return !(left == right);
}
