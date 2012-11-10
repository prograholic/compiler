#include "BufferedInputStream.h"

#include <boost/assert.hpp>
#include <boost/smart_ptr/make_shared.hpp>

BufferedInputStream::BufferedInputStream(InputStreamBase & inputStream)
	: mInputStream(inputStream),
	  mReadedData(boost::make_shared<StreamBuffer>()),
	  mCurrentPosition(0),
	  mCurrentScopePosition(0)
{

}

int BufferedInputStream::peek()
{
	BOOST_ASSERT(mCurrentPosition <= mReadedData->size());

	if (mCurrentPosition == mReadedData->size())
	{
		return mInputStream.peek();
	}
	else
	{
		BOOST_ASSERT(mCurrentPosition < mReadedData->size());
		return mReadedData->symbol(mCurrentPosition);
	}
}

int BufferedInputStream::next()
{
	BOOST_ASSERT(mCurrentPosition <= mReadedData->size());

	if (mCurrentPosition == mReadedData->size())
	{
		readToInternalBuffer();
	}
	BOOST_ASSERT(mCurrentPosition < mReadedData->size());

	int result = mReadedData->symbol(mCurrentPosition);

	++mCurrentPosition;
	return result;
}


Location BufferedInputStream::currentLocation()
{
	BOOST_ASSERT(mCurrentPosition <= mReadedData->size());

	if (mCurrentPosition == mReadedData->size())
	{
		return mInputStream.currentLocation();
	}
	else
	{
		BOOST_ASSERT(mCurrentPosition < mReadedData->size());
		return mReadedData->location(mCurrentPosition);
	}
}




void BufferedInputStream::markCurrentScope()
{
	BOOST_ASSERT(mCurrentPosition >= mCurrentScopePosition);

	mCurrentScopePosition = mCurrentPosition;
}


void BufferedInputStream::unwind()
{
	BOOST_ASSERT(mCurrentScopePosition <= mCurrentPosition);

	mCurrentPosition = mCurrentScopePosition;
}



StreamBufferPtr BufferedInputStream::buffer()
{
	return mReadedData;
}

size_t BufferedInputStream::currentScopePosition() const
{
	return mCurrentScopePosition;
}


size_t BufferedInputStream::currentPosition() const
{
	return mCurrentPosition;
}



///////////////////////// private implementation /////////////////////////


void BufferedInputStream::readToInternalBuffer()
{
	/// @note Order is important
	Location currentLocation = mInputStream.currentLocation();
	int currentSymbol = mInputStream.next();

	mReadedData->push_back(currentSymbol, currentLocation);
}
