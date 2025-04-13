#ifndef SOG_VECTOR2_H
#define SOG_VECTOR2_H

#include <sog/math/vec_core.h>

#define SOG_ENABLE_SWIZZLE_XY
#include <sog/math/swizzle_xy.h>

namespace sog {

union vec3;
union vec4;

#define VEC2_OPERATOR(_op) \
VEC_OPERATOR( vec2, float, _op, vec2{ _lhs.x _op _rhs,   _lhs.y _op _rhs   } ) \
VEC_OPERATOR(float,  vec2, _op, vec2{ _lhs   _op _rhs.x, _lhs   _op _rhs.y } ) \
VEC_OPERATOR( vec2,  vec2, _op, vec2{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y } ) 

#define VEC2i_OPERATOR(_op) \
VEC_OPERATOR(  vec2i, int32_t, _op, vec2i{ _lhs.x _op _rhs,   _lhs.y _op _rhs   } ) \
VEC_OPERATOR(int32_t,   vec2i, _op, vec2i{ _lhs   _op _rhs.x, _lhs   _op _rhs.y } ) \
VEC_OPERATOR(  vec2i,   vec2i, _op, vec2i{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y } ) 

union vec2
{
	struct { float x, y; };
	
	// TODO: __m64 for x86 platforms

	vec2() : x{ 0 }, y{ 0 } {}
	vec2( float _x, float _y ) : x{ _x }, y{ _y } {}
	
	float& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}

	SOG_SWIZZLE_XY;

};

union vec2i
{
	struct { int32_t x, y; };
	
	// TODO: __m64i for x86 platforms

	vec2i() : x{ 0 }, y{ 0 } {}
	vec2i( const sog::vec2& p_v2 ) : x{ (int32_t)p_v2.x }, y{ (int32_t)p_v2.y } {}
	vec2i( int32_t _x, int32_t _y ) : x{ _x }, y{ _y } {}

	int32_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}
};


VEC_DEFAULT_OPERATORS( VEC2_OPERATOR );
//VEC_DEFAULT_OPERATORS( VEC2i_OPERATOR );

}

#endif
