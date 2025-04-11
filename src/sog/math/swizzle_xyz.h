#ifndef SOG_SWIZZLE_XYZ_H
#define SOG_SWIZZLE_XYZ_H

/**
 * member definitions.
 */

#define SOG_SWIZZLE_XYZ_TYPE2(_a,_b) \
struct _a##_b##_t {                \
	float x, y, z;                         \
	operator sog::vec2();                  \
} _a##_b;

#define SOG_SWIZZLE_XYZ_TYPE3(_a,_b,_c) \
struct _a##_b##_c##_t {                \
	float x, y, z;                         \
	operator sog::vec3();                  \
} _a##_b##_c;

#define SOG_SWIZZLE_XYZ_TYPE4(_a,_b,_c,_d) \
struct _a##_b##_c##_d##_t {                \
	float x, y, z;                         \
	operator sog::vec4();                  \
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

/**
 * operators.
 */

#define SOG_SWIZZLE_OP_XYZ_TYPE2(_a,_b) \
sog::vec3::_a##_b##_t::operator sog::vec2() { return{ _a, _b }; }

#define SOG_SWIZZLE_OP_XYZ_TYPE3(_a,_b,_c) \
sog::vec3::_a##_b##_c##_t::operator sog::vec3() { return{ _a, _b, _c }; } 

#define SOG_SWIZZLE_OP_XYZ_TYPE4(_a,_b,_c,_d) \
sog::vec3::_a##_b##_c##_d##_t::operator sog::vec4() { return{ _a, _b, _c, _d }; }

#define SOG_SWIZZLE_OP_XYZ_CORE2(_a) \
SOG_SWIZZLE_OP_XYZ_TYPE2(_a,x)       \
SOG_SWIZZLE_OP_XYZ_TYPE2(_a,y)       \
SOG_SWIZZLE_OP_XYZ_TYPE2(_a,z)

#define SOG_SWIZZLE_OP_XYZ_CORE3(_a,_b) \
SOG_SWIZZLE_OP_XYZ_TYPE3(_a,_b,x)       \
SOG_SWIZZLE_OP_XYZ_TYPE3(_a,_b,y)       \
SOG_SWIZZLE_OP_XYZ_TYPE3(_a,_b,z)

#define SOG_SWIZZLE_OP_XYZ_CORE4(_a,_b,_c) \
SOG_SWIZZLE_OP_XYZ_TYPE4(_a,_b,_c,x)       \
SOG_SWIZZLE_OP_XYZ_TYPE4(_a,_b,_c,y)       \
SOG_SWIZZLE_OP_XYZ_TYPE4(_a,_b,_c,z)

#define SOG_SWIZZLE_OP_XYZ_C(_a,_b) \
SOG_SWIZZLE_OP_XYZ_CORE3(_a,_b)     \
SOG_SWIZZLE_OP_XYZ_CORE4(_a,_b,x)   \
SOG_SWIZZLE_OP_XYZ_CORE4(_a,_b,y)   \
SOG_SWIZZLE_OP_XYZ_CORE4(_a,_b,z)   

#define SOG_SWIZZLE_OP_XYZ_B(_a) \
SOG_SWIZZLE_OP_XYZ_CORE2(_a)     \
SOG_SWIZZLE_OP_XYZ_C(_a, x)      \
SOG_SWIZZLE_OP_XYZ_C(_a, y)      \
SOG_SWIZZLE_OP_XYZ_C(_a, z)

#define SOG_SWIZZLE_OP_XYZ \
SOG_SWIZZLE_OP_XYZ_B( x )  \
SOG_SWIZZLE_OP_XYZ_B( y )  \
SOG_SWIZZLE_OP_XYZ_B( z )

#endif
