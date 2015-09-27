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

typedef int8_t int8;    /* 8 bit signed */
typedef uint8_t uint8;  /* 8 bit unsigned */
typedef int16_t int16;  /* 16 bit signed */
typedef uint16_t uint16;/* 16 bit unsigned */
typedef int32_t int32;  /* 32 bit signed */
typedef uint32_t uint32;/* 32 bit unsigned */
typedef int64_t int64;  /* 64 bit signed */
typedef uint64_t uint64;/* 64 bit unsigned */

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef uint8 byte;
typedef double real;

}

#endif // SWAPI_TYPES_H
