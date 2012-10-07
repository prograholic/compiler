#ifndef COMPILER_CORE_STD_INPUT_STREAM_ADAPTER_H
#define COMPILER_CORE_STD_INPUT_STREAM_ADAPTER_H

#include <istream>

#include "core/InputStreamBase.h"


class StdInputStreamAdapter : public InputStreamBase
{
public:
	explicit StdInputStreamAdapter(std::istream * inputStream);

	virtual int peek();

	virtual int next();

	virtual Location currentLocation();


	void updateInputStream(std::istream & newInputStream);

private:

	std::istream * mInputStream;

	Location mCurrentLocation;


	void updateCurrentLocation(int symbol);
};

#endif // COMPILER_CORE_STD_INPUT_STREAM_ADAPTER_H
