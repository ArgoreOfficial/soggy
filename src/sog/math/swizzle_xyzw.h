#ifndef SOG_SWIZZLE_XYZWW_H
#define SOG_SWIZZLE_XYZWW_H

#include <sog/math/swizzle.h>

/**
 * member definitions.
 */

#define SOG_SWIZZLE_XYZW_TYPE2(_a,_b) \
struct _a##_b##_t {                   \
	float x, y, z, w;                 \
	SOG_TY_TYPECAST_2(_a,_b)            \
} _a##_b;

#define SOG_SWIZZLE_XYZW_TYPE3(_a,_b,_c) \
struct _a##_b##_c##_t   {                \
	float x, y, z, w;                    \
	_a##_b##_c##_t() = default;          \
	_a##_b##_c##_t( const sog::vec3& p_v3 ) : x{p_v3.x}, y{p_v3.y}, z{p_v3.z} {} \
	SOG_TY_TYPECAST_3(_a,_b,_c) \
} _a##_b##_c;

#define SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,_d) \
struct _a##_b##_c##_d##_t {                 \
	float x, y, z, w;                       \
	SOG_TY_TYPECAST_4(_a,_b,_c,_d) \
} _a##_b##_c##_d;

#define SOG_SWIZZLE_XYZW_CORE2(_a) \
SOG_SWIZZLE_XYZW_TYPE2(_a,x)       \
SOG_SWIZZLE_XYZW_TYPE2(_a,y)       \
SOG_SWIZZLE_XYZW_TYPE2(_a,z)       \
SOG_SWIZZLE_XYZW_TYPE2(_a,w)

#define SOG_SWIZZLE_XYZW_CORE3(_a,_b) \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,x)       \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,y)       \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,z)       \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,w)

#define SOG_SWIZZLE_XYZW_CORE4(_a,_b,_c) \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,x)       \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,y)       \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,z)       \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,w)

#define SOG_SWIZZLE_XYZW_C(_a,_b) \
SOG_SWIZZLE_XYZW_CORE3(_a,_b)     \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,x)   \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,y)   \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,z)   \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,w)

#define SOG_SWIZZLE_XYZW_B(_a) \
SOG_SWIZZLE_XYZW_CORE2(_a)     \
SOG_SWIZZLE_XYZW_C(_a, x)      \
SOG_SWIZZLE_XYZW_C(_a, y)      \
SOG_SWIZZLE_XYZW_C(_a, z)      \
SOG_SWIZZLE_XYZW_C(_a, w)

#define SOG_SWIZZLE_XYZW \
SOG_SWIZZLE_XYZW_B(x)    \
SOG_SWIZZLE_XYZW_B(y)    \
SOG_SWIZZLE_XYZW_B(z)    \
SOG_SWIZZLE_XYZW_B(w)

#endif