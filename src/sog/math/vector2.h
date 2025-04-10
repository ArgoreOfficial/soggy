#ifndef SOG_VECTOR2_H
#define SOG_VECTOR2_H

#include <sog/math/vec_core.h>

namespace sog {

#define VEC2_OPERATOR(_op) \
VEC_OPERATOR(vec2, decimal_type_t, _op, vec2{ _lhs.x _op _rhs,   _lhs.y _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec2, _op, vec2{ _lhs   _op _rhs.x, _lhs   _op _rhs.y } ) \
VEC_OPERATOR(vec2,       vec2, _op, vec2{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y } ) 

#define SWIZZLE_XY_MEMBERS \
SWIZZLE_2_XY( x, x, float ); \
SWIZZLE_2_XY( x, y, float ); \
SWIZZLE_2_XY( y, x, float ); \
SWIZZLE_2_XY( y, y, float );

union vec2
{
	struct { float x, y; };

	vec2() : x{ 0 }, y{ 0 } {}
	vec2( float _x, float _y ) : x{ _x }, y{ _y } {}

	SWIZZLE_XY_MEMBERS;

	decimal_type_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}
};

VEC_DEFAULT_OPERATORS( VEC2_OPERATOR );

}

#endif
