#include "StreamBuffer.h"

#include <boost/assert.hpp>


#define ENSURE_BUFFERS_SYNC(sym, loc) BOOST_ASSERT((sym).size() == (loc).size())

StreamBuffer::StreamBuffer()
{
}


size_t StreamBuffer::size() const
{
	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);

	return mSymbols.size();
}

StreamBuffer::value_type & StreamBuffer::symbol(size_t pos)
{
	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);

	return mSymbols[pos];
}

StreamBuffer::value_type StreamBuffer::symbol(size_t pos) const
{
	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);

	return mSymbols[pos];
}

Location & StreamBuffer::location(size_t pos)
{
	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);

	return mLocations[pos];
}


const Location & StreamBuffer::location(size_t pos) const
{
	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);

	return mLocations[pos];
}


void StreamBuffer::push_back(char symbol, const Location & loc)
{
	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);


	/// @todo check for exception (may get inconsistent buffer)

	mSymbols.push_back(symbol);
	mLocations.push_back(loc);

	ENSURE_BUFFERS_SYNC(mSymbols, mLocations);
}
