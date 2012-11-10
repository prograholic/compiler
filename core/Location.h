#ifndef COMPILER_CORE_LOCATION_H
#define COMPILER_CORE_LOCATION_H

#include <cstddef>

struct Location
{
	size_t line;
	size_t colon;

	Location();

	Location(size_t l, size_t c);

	void clear();
};


bool operator == (const Location & tl1, const Location & tl2);

inline bool operator != (const Location & tl1, const Location & tl2)
{
	return !(tl1 == tl2);
}

#endif // COMPILER_CORE_LOCATION_H
