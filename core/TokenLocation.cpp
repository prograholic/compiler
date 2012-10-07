#include "TokenLocation.h"




TokenLocation::TokenLocation()
	: line(0),
	  colon(0)
{}

TokenLocation::TokenLocation(size_t l, size_t c)
	: line(l),
	  colon(c)
{}


bool operator == (const TokenLocation & tl1, const TokenLocation & tl2)
{
	if (tl1.colon != tl2.colon)
	{
		return false;
	}

	if (tl1.line != tl2.line)
	{
		return false;
	}

	return true;
}
