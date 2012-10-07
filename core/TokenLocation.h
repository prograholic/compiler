#ifndef COMPILER_CORE_TOKEN_LOCATION_H
#define COMPILER_CORE_TOKEN_LOCATION_H

#include <cstddef>

struct TokenLocation
{
	size_t line;
	size_t colon;

	TokenLocation();

	TokenLocation(size_t l, size_t c);
};


bool operator == (const TokenLocation & tl1, const TokenLocation & tl2);

inline bool operator != (const TokenLocation & tl1, const TokenLocation & tl2)
{
	return !(tl1 == tl2);
}

#endif // COMPILER_CORE_TOKEN_LOCATION_H
