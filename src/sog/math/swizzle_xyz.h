#ifndef SOG_SWIZZLE_XYZ_H
#define SOG_SWIZZLE_XYZ_H

#include <sog/math/swizzle.h>

/**
 * member definitions.
 */

#define SOG_SWIZZLE_XYZ_TYPE2(_a,_b) \
struct _a##_b##_t {                  \
	float x, y, z;                   \
	SOG_TY_TYPECAST_2(_a,_b)            \
} _a##_b;

#define SOG_SWIZZLE_XYZ_TYPE3(_a,_b,_c) \
struct _a##_b##_c##_t {                 \
	float x, y, z;                      \
	SOG_TY_TYPECAST_3(_a,_b,_c)           \
} _a##_b##_c;

#define SOG_SWIZZLE_XYZ_TYPE4(_a,_b,_c,_d) \
struct _a##_b##_c##_d##_t {                \
	float x, y, z;                         \
	SOG_TY_TYPECAST_4(_a,_b,_c,_d)           \
} _a##_b##_c##_d;

#define SOG_SWIZZLE_XYZ_CORE2(_a) \
SOG_SWIZZLE_XYZ_TYPE2(_a,x)       \
SOG_SWIZZLE_XYZ_TYPE2(_a,y)       \
SOG_SWIZZLE_XYZ_TYPE2(_a,z)

#define SOG_SWIZZLE_XYZ_CORE3(_a,_b) \
SOG_SWIZZLE_XYZ_TYPE3(_a,_b,x)       \
SOG_SWIZZLE_XYZ_TYPE3(_a,_b,y)       \
SOG_SWIZZLE_XYZ_TYPE3(_a,_b,z)

#define SOG_SWIZZLE_XYZ_CORE4(_a,_b,_c) \
SOG_SWIZZLE_XYZ_TYPE4(_a,_b,_c,x)       \
SOG_SWIZZLE_XYZ_TYPE4(_a,_b,_c,y)       \
SOG_SWIZZLE_XYZ_TYPE4(_a,_b,_c,z)

#define SOG_SWIZZLE_XYZ_C(_a,_b) \
SOG_SWIZZLE_XYZ_CORE3(_a,_b)     \
SOG_SWIZZLE_XYZ_CORE4(_a,_b,x)   \
SOG_SWIZZLE_XYZ_CORE4(_a,_b,y)   \
SOG_SWIZZLE_XYZ_CORE4(_a,_b,z)   \

#define SOG_SWIZZLE_XYZ_B(_a) \
SOG_SWIZZLE_XYZ_CORE2(_a)     \
SOG_SWIZZLE_XYZ_C(_a, x)      \
SOG_SWIZZLE_XYZ_C(_a, y)      \
SOG_SWIZZLE_XYZ_C(_a, z)

#define SOG_SWIZZLE_XYZ \
SOG_SWIZZLE_XYZ_B(x)    \
SOG_SWIZZLE_XYZ_B(y)    \
SOG_SWIZZLE_XYZ_B(z)

#endif