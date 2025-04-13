#ifndef SOG_VECTOR4_H
#define SOG_VECTOR4_H

#include <sog/math/vector3.h>

#define SOG_ENABLE_SWIZZLE_XYZW
#include <sog/math/swizzle_xyzw.h>

namespace sog {

#define VEC4_OPERATOR(_op) \
VEC_OPERATOR(sog::vec4,     float, _op, sog::vec4{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs,   _lhs.w _op _rhs   } ) \
VEC_OPERATOR(    float, sog::vec4, _op, sog::vec4{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z, _lhs   _op _rhs.w } ) \
VEC_OPERATOR(sog::vec4, sog::vec4, _op, sog::vec4{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z, _lhs.w _op _rhs.w } ) 

union vec4
{
	struct { float x, y, z, w; };
// #ifdef SOG_SIMD
	__m128 v128;
	vec4( __m128 p_v128 ) : 
		v128{ p_v128 } 
	{ }
// #endif

	vec4( void ) : 
		x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } 
	{ }

	vec4( float _x, float _y, float _z, float _w ) : 
		x{ _x }, y{ _y }, z{ _z }, w{ _w } 
	{ }
	
	vec4( const vec3& _vec, float _w ) :
		xyz( _vec )
	{ 
		w = _w;
	}

	float& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}

	vec4& operator +=( const vec4& p_rhs ) {
		v128 = _mm_add_ps( v128, p_rhs.v128 );
		return *this;
	}

	vec4& operator -=( const vec4& p_rhs ) {
		v128 = _mm_sub_ps( v128, p_rhs.v128 );
		return *this;
	}

	struct rgba8_t
	{
		struct { float x, y, z, w; };
		operator uint32_t();
	} rgba8;

	struct bgra8_t
	{
		struct { float x, y, z, w; };
		operator uint32_t();
	} bgra8;

	SOG_SWIZZLE_XYZW;
};

VEC_DEFAULT_OPERATORS( VEC4_OPERATOR );

union vec4i
{
	struct { int32_t x, y, z, w; };
// #ifdef SOG_SIMD
	__m128i v128i;
	vec4i( __m128i p_v128i ) : 
		v128i{ p_v128i } 
	{ }
// #endif

	vec4i( void ) : x{ 0 }, y{ 0 }, z{ 0 }, w{ 0 } {}
	vec4i( int32_t _x, int32_t _y, int32_t _z, int32_t _w ) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}

	int32_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}

	vec4i& operator +=( const vec4i& p_rhs ) {
		v128i = _mm_add_epi32( v128i, p_rhs.v128i );
		return *this;
	}

	vec4i& operator -=( const vec4i& p_rhs ) {
		v128i = _mm_add_epi32( v128i, p_rhs.v128i );
		return *this;
	}

};

inline vec4i operator +( const vec4i& p_lhs, const vec4i& p_rhs ) {
	return vec4i{ _mm_add_epi32( p_lhs.v128i, p_rhs.v128i ) };
}

inline vec4i operator -( const vec4i& p_lhs, const vec4i& p_rhs ) {
	return vec4i{ _mm_sub_epi32( p_lhs.v128i, p_rhs.v128i ) };
}

}

#endif
