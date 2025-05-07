#ifndef SOG_VECTOR3_H
#define SOG_VECTOR3_H

#include <sog/math/vector2.h>

#define SOG_ENABLE_SWIZZLE_XYZ
#include <sog/math/swizzle_xyz.h>

namespace sog {

#define VEC3_OPERATOR(_op) \
VEC_OPERATOR( vec3, float, _op, vec3{ _lhs.x() _op _rhs,   _lhs.y() _op _rhs,   _lhs.z() _op _rhs   } ) \
VEC_OPERATOR(float,  vec3, _op, vec3{ _lhs   _op _rhs.x(), _lhs   _op _rhs.y(), _lhs   _op _rhs.z() } ) \
VEC_OPERATOR( vec3,  vec3, _op, vec3{ _lhs.x() _op _rhs.x(), _lhs.y() _op _rhs.y(), _lhs.z() _op _rhs.z() } ) 

struct vec3
{
	typedef float Ty;
	static constexpr size_t SIZE = 3;

	union
	{
		float buf[ SIZE ] = { 0.0f }; // TODO: __m64 for x86 platforms
		SOG_SWIZZLE_XYZ;
	};

	vec3( void ) = default;

	vec3( float _v )                     : xyz{ _v, _v, _v } {}
	vec3( float _x, float _y, float _z ) : xyz{ _x, _y, _z } { }

	float& operator[]( const size_t _idx ) { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	
	float& x() { return buf[ 0 ]; } float x() const { return buf[ 0 ]; }
	float& r() { return x();      } float r() const { return x();      }
	float& u() { return x();      } float u() const { return x();      }

	float& y() { return buf[ 1 ]; } float y() const { return buf[ 1 ]; }
	float& g() { return y();      } float g() const { return y();      }
	float& v() { return y();      } float v() const { return y();      }

	float& z() { return buf[ 2 ]; } float z() const { return buf[ 2 ]; } 
	float& b() { return z();      } float b() const { return z();      } 


};

VEC_DEFAULT_OPERATORS( VEC3_OPERATOR );

inline vec3& operator +=( vec3& _a, const vec3& _b ) { _a = _a + _b; return _a; }
inline vec3& operator -=( vec3& _a, const vec3& _b ) { _a = _a - _b; return _a; }
inline vec3& operator *=( vec3& _a, const vec3& _b ) { _a = _a * _b; return _a; }
inline vec3& operator /=( vec3& _a, const vec3& _b ) { _a = _a / _b; return _a; }

}

#endif 
