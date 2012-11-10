#ifndef COMPILER_CORE_STREAM_BUFFER_H
#define COMPILER_CORE_STREAM_BUFFER_H

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>


#include "core/Location.h"


class StreamBuffer : private boost::noncopyable
{
public:

	typedef char value_type;

	StreamBuffer();

	size_t size() const;

	value_type & symbol(size_t pos);

	value_type symbol(size_t pos) const;

	Location & location(size_t pos);

	const Location & location(size_t pos) const;


	void push_back(char symbol, const Location & loc);


private:

	typedef std::vector<char> BufferEntries;
	typedef std::vector<Location> LocationEntries;

	BufferEntries mSymbols;
	LocationEntries mLocations;
};




typedef boost::shared_ptr<StreamBuffer> StreamBufferPtr;

#endif // COMPILER_CORE_STREAM_BUFFER_H
