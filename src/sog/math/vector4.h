#ifndef SOG_VECTOR4_H
#define SOG_VECTOR4_H

#include <sog/math/vector3.h>

namespace sog {

#define VEC4_OPERATOR(_op) \
VEC_OPERATOR(vec4, decimal_type_t, _op, vec4{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs,   _lhs.w _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec4, _op, vec4{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z, _lhs   _op _rhs.w } ) \
VEC_OPERATOR(vec4,           vec4, _op, vec4{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z, _lhs.w _op _rhs.w } ) 

#define SWIZZLE_XYZW_MEMBERS \
SWIZZLE_2_XYZW( x, w, float ); \
SWIZZLE_2_XYZW( y, w, float ); \
SWIZZLE_2_XYZW( z, w, float ); \
SWIZZLE_2_XYZW( w, x, float ); \
SWIZZLE_2_XYZW( w, y, float ); \
SWIZZLE_2_XYZW( w, z, float ); \
SWIZZLE_2_XYZW( w, w, float );

union vec4
{
	struct { float x, y, z, w; };

	vec4( void ) : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {}
	vec4( float _x, float _y, float _z, float _w ) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}
	
	vec4( const vec3& _vec, float _w ) : x{ _vec.x }, y{ _vec.y }, z{ _vec.z }, w{ _w } {}

	SWIZZLE_XY_MEMBERS;
	SWIZZLE_XYZ_MEMBERS;
	SWIZZLE_XYZW_MEMBERS;

	decimal_type_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}
};

VEC_DEFAULT_OPERATORS( VEC4_OPERATOR );

}

#endif
