#ifndef SWAPI_TYPES_H
#define SWAPI_TYPES_H

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define SWAPI_64BITS
#else
#define SWAPI_32BITS
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define SWAPI_64BITS
#else
#define SWAPI_32BITS
#endif
#endif

#include <cstdint>

namespace hsm{

typedef uint8_t byte;
typedef double real;

}

#endif // SWAPI_TYPES_H
