#include "core/Location.h"




Location::Location()
	: line(0),
	  colon(0)
{}

Location::Location(size_t l, size_t c)
	: line(l),
	  colon(c)
{}


bool operator == (const Location & tl1, const Location & tl2)
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
