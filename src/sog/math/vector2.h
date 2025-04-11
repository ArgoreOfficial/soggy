#ifndef SOG_VECTOR2_H
#define SOG_VECTOR2_H

#include <sog/math/vec_core.h>
#include <sog/math/swizzle.h>

namespace sog {

union vec3;
union vec4;

#define VEC2_OPERATOR(_op) \
VEC_OPERATOR(vec2, decimal_type_t, _op, vec2{ _lhs.x _op _rhs,   _lhs.y _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec2, _op, vec2{ _lhs   _op _rhs.x, _lhs   _op _rhs.y } ) \
VEC_OPERATOR(vec2,       vec2, _op, vec2{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y } ) 

union vec2
{
	struct { float x, y; };

	vec2() : x{ 0 }, y{ 0 } {}
	vec2( float _x, float _y ) : x{ _x }, y{ _y } {}
	
	decimal_type_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}

	SOG_SWIZZLE_XY;

};

VEC_DEFAULT_OPERATORS( VEC2_OPERATOR );

}

#endif
