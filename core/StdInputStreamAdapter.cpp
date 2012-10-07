#include "StdInputStreamAdapter.h"

#include <boost/assert.hpp>

StdInputStreamAdapter::StdInputStreamAdapter(std::istream * inputStream)
	: mInputStream(inputStream)
{
}


int StdInputStreamAdapter::peek()
{
	BOOST_ASSERT(mInputStream);
	return mInputStream->peek();
}

int StdInputStreamAdapter::next()
{
	BOOST_ASSERT(mInputStream);
	int symbol = mInputStream->get();
	updateCurrentLocation(symbol);

	return symbol;
}

Location StdInputStreamAdapter::currentLocation()
{
	return mCurrentLocation;
}



void StdInputStreamAdapter::updateInputStream(std::istream & newInputStream)
{
	mInputStream = &newInputStream;

	BOOST_ASSERT(mInputStream);
}




//////////////////////////////// Private implementation ////////////////////////////////


void StdInputStreamAdapter::updateCurrentLocation(int symbol)
{
	if (symbol == '\n')
	{
		++mCurrentLocation.line;
		mCurrentLocation.colon = 0;
	}
	else
	{
		++mCurrentLocation.colon;
	}
}
