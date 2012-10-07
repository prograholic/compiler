#ifndef COMPILER_CORE_ERROR_H
#define COMPILER_CORE_ERROR_H

#include "core/TokenLocation.h"
#include "core/ErrorCodes.h"


struct Error
{
	Error(ErrorCodes errorCode, const TokenLocation & location);

	ErrorCodes errorCode;

	TokenLocation location;
};




#endif // COMPILER_CORE_ERROR_H
