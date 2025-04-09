#ifndef SOG_VECTOR3_H
#define SOG_VECTOR3_H

#include <sog/math/vector2.h>

namespace sog {

#define VEC3_OPERATOR(_op) \
VEC_OPERATOR(vec3<Ty>, decimal_type_t, _op, vec3<Ty>{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec3<Ty>, _op, vec3<Ty>{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z } ) \
VEC_OPERATOR(vec3<Ty>,       vec3<Ty>, _op, vec3<Ty>{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z } ) 

#define SWIZZLE_XYZ_MEMBERS \
SWIZZLE_2_XYZ( x, z, Ty ); \
SWIZZLE_2_XYZ( y, z, Ty ); \
SWIZZLE_2_XYZ( z, x, Ty ); \
SWIZZLE_2_XYZ( z, y, Ty ); \
SWIZZLE_2_XYZ( z, z, Ty );

template<typename Ty>
union vec3
{
	struct { Ty x, y, z; };

	vec3( void ) : x{ 0 }, y{ 0 }, z{ 0 } {};
	vec3( Ty _v ) : x{ _v }, y{ _v }, z{ _v } {};
	vec3( Ty _x, Ty _y, Ty _z ) : x{ _x }, y{ _y }, z{ _z } {};

	SWIZZLE_XY_MEMBERS;
	SWIZZLE_XYZ_MEMBERS;

	decimal_type_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}
};

typedef vec3<float>  vec3f;
typedef vec3<double> vec3d;

VEC_DEFAULT_OPERATORS( VEC3_OPERATOR );

inline vec3f& operator +=( vec3f& _a, const vec3f& _b ) { _a = _a + _b; return _a; }
inline vec3f& operator -=( vec3f& _a, const vec3f& _b ) { _a = _a - _b; return _a; }
inline vec3f& operator *=( vec3f& _a, const vec3f& _b ) { _a = _a * _b; return _a; }
inline vec3f& operator /=( vec3f& _a, const vec3f& _b ) { _a = _a / _b; return _a; }

}

#endif 
