#include "Error.h"

Error::Error(ErrorCodes errCode, const TokenLocation & loc)
	: errorCode(errCode),
	  location(loc)
{
}
