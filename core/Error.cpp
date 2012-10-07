#include "Error.h"

Error::Error(ErrorCodes errCode, const Location & loc)
	: errorCode(errCode),
	  location(loc)
{
}
