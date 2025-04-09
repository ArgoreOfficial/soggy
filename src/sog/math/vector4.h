#ifndef SOG_VECTOR4_H
#define SOG_VECTOR4_H

#include <sog/math/vector3.h>

namespace sog {

#define VEC4_OPERATOR(_op) \
VEC_OPERATOR(vec4<Ty>, decimal_type_t, _op, vec4<Ty>{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs,   _lhs.w _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec4<Ty>, _op, vec4<Ty>{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z, _lhs   _op _rhs.w } ) \
VEC_OPERATOR(vec4<Ty>,       vec4<Ty>, _op, vec4<Ty>{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z, _lhs.w _op _rhs.w } ) 

#define SWIZZLE_XYZW_MEMBERS \
SWIZZLE_2_XYZW( x, w, Ty ); \
SWIZZLE_2_XYZW( y, w, Ty ); \
SWIZZLE_2_XYZW( z, w, Ty ); \
SWIZZLE_2_XYZW( w, x, Ty ); \
SWIZZLE_2_XYZW( w, y, Ty ); \
SWIZZLE_2_XYZW( w, z, Ty ); \
SWIZZLE_2_XYZW( w, w, Ty );

template<typename Ty>
union vec4
{
	struct { Ty x, y, z, w; };

	vec4( void ) : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {}
	vec4( Ty _x, Ty _y, Ty _z, Ty _w ) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}
	
	template<typename Ty2> 
	vec4( const vec3<Ty2>& _vec, Ty _w ) : x{ _vec.x }, y{ _vec.y }, z{ _vec.z }, w{ _w } {}

	SWIZZLE_XY_MEMBERS;
	SWIZZLE_XYZ_MEMBERS;
	SWIZZLE_XYZW_MEMBERS;
};

typedef vec4<float>  vec4f;
typedef vec4<double> vec4d;

VEC_DEFAULT_OPERATORS( VEC4_OPERATOR );

}

#endif
