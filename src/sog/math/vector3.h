#ifndef SOG_VECTOR3_H
#define SOG_VECTOR3_H

#include <sog/math/vector2.h>

#define SOG_ENABLE_SWIZZLE_XYZ
#include <sog/math/swizzle_xyz.h>

namespace sog {

union vec4;

#define VEC3_OPERATOR(_op) \
VEC_OPERATOR( vec3, float, _op, vec3{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs   } ) \
VEC_OPERATOR(float,  vec3, _op, vec3{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z } ) \
VEC_OPERATOR( vec3,  vec3, _op, vec3{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z } ) 

union vec3
{
	struct { float x, y, z; };

	vec3( void ) : x{ 0 }, y{ 0 }, z{ 0 } {};
	vec3( float _v ) : x{ _v }, y{ _v }, z{ _v } {};
	vec3( float _x, float _y, float _z ) : x{ _x }, y{ _y }, z{ _z } {};

	float& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}

	SOG_SWIZZLE_XYZ;
};

VEC_DEFAULT_OPERATORS( VEC3_OPERATOR );

inline vec3& operator +=( vec3& _a, const vec3& _b ) { _a = _a + _b; return _a; }
inline vec3& operator -=( vec3& _a, const vec3& _b ) { _a = _a - _b; return _a; }
inline vec3& operator *=( vec3& _a, const vec3& _b ) { _a = _a * _b; return _a; }
inline vec3& operator /=( vec3& _a, const vec3& _b ) { _a = _a / _b; return _a; }

}

#endif 
