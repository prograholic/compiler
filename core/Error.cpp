#include "Error.h"

Error::Error(ErrorCodes errCode, const Location & loc)
	: errorCode(errCode),
	  location(loc)
{
}


void Error::clear()
{
	errorCode = EC_NoError;
	location.clear();
}
