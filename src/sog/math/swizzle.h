#ifndef SOG_SWIZZLE_H
#define SOG_SWIZZLE_H

#define SOG_SWIZZLE_XYZ_TYPE2(_a,_b) \
struct { \
	float x, y, z; \
	sog::vec2 get() { return {}; } \
} _a##_b; \

#define SOG_SWIZZLE_XYZ_TYPE3(_a,_b,_c) \
struct { \
	float x, y, z; \
	sog::vec3 get() { return {_a,_b,_c}; } \
} _a##_b##_c; \

#define SOG_SWIZZLE_XYZ_TYPE4(_a,_b,_c,_d) \
struct { \
	float x, y, z; \
	sog::vec4 get() { return {_a,_b,_c,_d}; } \
} _a##_b##_c##_d; \

#define SOG_SWIZZLE_XYZ_CORE(_a) \
SOG_SWIZZLE_XYZ_TYPE2(_a,x)\
SOG_SWIZZLE_XYZ_TYPE2(_a,y)\
SOG_SWIZZLE_XYZ_TYPE2(_a,z)

#define SOG_SWIZZLE_XYZ_C(_a,_b) \
SOG_SWIZZLE_XYZ_CORE(_a##_b)     \
SOG_SWIZZLE_XYZ_CORE(_a##_b##x)  \
SOG_SWIZZLE_XYZ_CORE(_a##_b##y)  \
SOG_SWIZZLE_XYZ_CORE(_a##_b##z)  \

#define SOG_SWIZZLE_XYZ_B(_a) \
SOG_SWIZZLE_XYZ_CORE(_a)      \
SOG_SWIZZLE_XYZ_C(_a, x)      \
SOG_SWIZZLE_XYZ_C(_a, y)      \
SOG_SWIZZLE_XYZ_C(_a, z)

#define SOG_SWIZZLE_XYZ \
SOG_SWIZZLE_XYZ_B( x )  \
SOG_SWIZZLE_XYZ_B( y )  \
SOG_SWIZZLE_XYZ_B( z )


#endif