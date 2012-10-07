#include "BufferedInputStream.h"

#include <boost/assert.hpp>

BufferedInputStream::BufferedInputStream(InputStreamBase & inputStream)
	: mInputStream(inputStream),
	  mReadedData(),
	  mCurrentPosition(0),
	  mCurrentScopePosition(0)
{

}

int BufferedInputStream::peek()
{
	BOOST_ASSERT(mCurrentPosition <= mReadedData.size());

	if (mCurrentPosition == mReadedData.size())
	{
		return mInputStream.peek();
	}
	else
	{
		BOOST_ASSERT(mCurrentPosition < mReadedData.size());
		return mReadedData[mCurrentPosition].first;
	}
}

int BufferedInputStream::next()
{
	BOOST_ASSERT(mCurrentPosition <= mReadedData.size());

	if (mCurrentPosition == mReadedData.size())
	{
		readToInternalBuffer();
	}
	BOOST_ASSERT(mCurrentPosition < mReadedData.size());

	int result = mReadedData[mCurrentPosition].first;

	++mCurrentPosition;
	return result;
}


Location BufferedInputStream::currentLocation()
{
	BOOST_ASSERT(mCurrentPosition <= mReadedData.size());

	if (mCurrentPosition == mReadedData.size())
	{
		return mInputStream.currentLocation();
	}
	else
	{
		BOOST_ASSERT(mCurrentPosition < mReadedData.size());
		return mReadedData[mCurrentPosition].second;
	}
}




void BufferedInputStream::markCurrentScope()
{
	BOOST_ASSERT(mCurrentPosition >= mCurrentScopePosition);

	mCurrentScopePosition = mCurrentPosition;
}


void BufferedInputStream::unwind()
{
	BOOST_ASSERT(mCurrentScopePosition >= mCurrentPosition);

	mCurrentPosition = mCurrentScopePosition;
}




///////////////////////// private implementation /////////////////////////


void BufferedInputStream::readToInternalBuffer()
{
	/// @note Order is important
	Location currentLocation = mInputStream.currentLocation();
	int currentSymbol = mInputStream.next();

	BufferEntry e = std::make_pair(currentSymbol, currentLocation);
	mReadedData.push_back(e);
}
