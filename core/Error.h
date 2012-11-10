#ifndef COMPILER_CORE_ERROR_H
#define COMPILER_CORE_ERROR_H

#include "core/Location.h"
#include "core/ErrorCodes.h"


struct Error
{
	explicit Error(ErrorCodes errorCode, const Location & location = Location());

	void clear();

	ErrorCodes errorCode;

	Location location;


};




#endif // COMPILER_CORE_ERROR_H
