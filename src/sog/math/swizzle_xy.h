#ifndef SOG_SWIZZLE_XY_H
#define SOG_SWIZZLE_XY_H

#include <sog/math/swizzle.h>

/**
 * member definitions.
 */

#define SOG_SWIZZLE_XY_TYPE2(_a,_b) \
struct _a##_b##_t {                 \
	float x, y;                     \
	SOG_TY_TYPECAST_2(_a,_b)          \
} _a##_b;

#define SOG_SWIZZLE_XY_TYPE3(_a,_b,_c) \
struct _a##_b##_c##_t {                \
	float x, y;                        \
	SOG_TY_TYPECAST_3(_a,_b,_c)          \
} _a##_b##_c;

#define SOG_SWIZZLE_XY_TYPE4(_a,_b,_c,_d) \
struct _a##_b##_c##_d##_t {               \
	float x, y;                           \
	SOG_TY_TYPECAST_4(_a,_b,_c,_d)          \
} _a##_b##_c##_d;

#define SOG_SWIZZLE_XY_CORE2(_a) \
SOG_SWIZZLE_XY_TYPE2(_a,x)       \
SOG_SWIZZLE_XY_TYPE2(_a,y)

#define SOG_SWIZZLE_XY_CORE3(_a,_b) \
SOG_SWIZZLE_XY_TYPE3(_a,_b,x)       \
SOG_SWIZZLE_XY_TYPE3(_a,_b,y)

#define SOG_SWIZZLE_XY_CORE4(_a,_b,_c) \
SOG_SWIZZLE_XY_TYPE4(_a,_b,_c,x)       \
SOG_SWIZZLE_XY_TYPE4(_a,_b,_c,y)

#define SOG_SWIZZLE_XY_C(_a,_b) \
SOG_SWIZZLE_XY_CORE3(_a,_b)     \
SOG_SWIZZLE_XY_CORE4(_a,_b,x)   \
SOG_SWIZZLE_XY_CORE4(_a,_b,y)

#define SOG_SWIZZLE_XY_B(_a) \
SOG_SWIZZLE_XY_CORE2(_a)     \
SOG_SWIZZLE_XY_C(_a, x)      \
SOG_SWIZZLE_XY_C(_a, y)

#define SOG_SWIZZLE_XY \
SOG_SWIZZLE_XY_B(x)    \
SOG_SWIZZLE_XY_B(y)

#endif