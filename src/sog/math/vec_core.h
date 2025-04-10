#ifndef SOG_MATH_VEC_CORE_H
#define SOG_MATH_VEC_CORE_H

namespace sog {

typedef float decimal_type_t;

}

#define SWIZZLE_2( _a, _b, ... ) \
struct { __VA_ARGS__; \
	inline operator vec2() const { return { _a, _b }; } } \
_a##_b

#define SWIZZLE_3( _a, _b, _c, ... ) \
struct { __VA_ARGS__; \
	inline operator vec3() const { return { _a, _b, _c }; } } \
_a##_b##_c

#define SWIZZLE_2_XY( _a, _b, _ty )   SWIZZLE_2( _a, _b, _ty x, y )
#define SWIZZLE_2_XYZ( _a, _b, _ty )  SWIZZLE_2( _a, _b, _ty x, y, z )
#define SWIZZLE_2_XYZW( _a, _b, _ty ) SWIZZLE_2( _a, _b, _ty x, y, z, w )

#define SWIZZLE_3_XY( _a, _b, _c, _ty )   SWIZZLE_3( _a, _b, _c, _ty x, y )
#define SWIZZLE_3_XYZ( _a, _b, _c, _ty )  SWIZZLE_3( _a, _b, _c, _ty x, y, z )
#define SWIZZLE_3_XYZW( _a, _b, _c, _ty ) SWIZZLE_3( _a, _b, _c, _ty x, y, z, w )

#define VEC_OPERATOR(_lhsTy,_rhsTy,_op,...) \
inline auto operator##_op##( const _lhsTy& _lhs, const _rhsTy& _rhs ) { \
	return __VA_ARGS__; \
}

#define VEC_DEFAULT_OPERATORS(_m) _m( / ); _m( * ); _m( + ); _m( - );


#endif
