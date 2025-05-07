#ifndef SOG_VECTOR4_H
#define SOG_VECTOR4_H

#include <sog/math/vector3.h>

#define SOG_ENABLE_SWIZZLE_XYZW
#include <sog/math/swizzle_xyzw.h>

namespace sog {

#define VEC4_OPERATOR(_op) \
VEC_OPERATOR(sog::vec4,     float, _op, sog::vec4{ _lhs.x() _op _rhs,   _lhs.y() _op _rhs,   _lhs.z() _op _rhs,   _lhs.w() _op _rhs   } ) \
VEC_OPERATOR(    float, sog::vec4, _op, sog::vec4{ _lhs   _op _rhs.x(), _lhs   _op _rhs.y(), _lhs   _op _rhs.z(), _lhs   _op _rhs.w() } ) \
VEC_OPERATOR(sog::vec4, sog::vec4, _op, sog::vec4{ _lhs.x() _op _rhs.x(), _lhs.y() _op _rhs.y(), _lhs.z() _op _rhs.z(), _lhs.w() _op _rhs.w() } ) 

struct vec4
{
	typedef float Ty;
	static constexpr size_t SIZE = 4;

	union
	{
		float buf[ SIZE ] = { 0.0f }; // TODO: __m64 for x86 platforms
// #ifdef SOG_SIMD
		__m128 v128;
// #endif
		SOG_SWIZZLE_XYZW;
	};

	vec4( void ) : 
		xyzw{ 0.0f, 0.0f, 0.0f, 0.0f }
	{ }

	vec4( float _x, float _y, float _z, float _w ) : 
		xyzw{ _x, _y, _z, _w }
	{ }
	
	vec4( __m128 p_v128 ) : 
		v128{ p_v128 } 
	{}

	vec4( const vec3& _vec, float _w ) : 
		xyzw{ _vec.x(), _vec.y(), _vec.z(), _w}
	{ }

	vec4& operator +=( const vec4& p_rhs ) {
		v128 = _mm_add_ps( v128, p_rhs.v128 );
		return *this;
	}

	vec4& operator -=( const vec4& p_rhs ) {
		v128 = _mm_sub_ps( v128, p_rhs.v128 );
		return *this;
	}

	float& operator[]( const size_t _idx ) { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	uint32_t rgba8() {
		swizzle_vec4<vec4, uint8_t, 4, 0, 1, 2, 3> rgba{ 
			static_cast<uint8_t>( x() * 255 ), 
			static_cast<uint8_t>( y() * 255 ), 
			static_cast<uint8_t>( z() * 255 ), 
			static_cast<uint8_t>( w() * 255 ) 
		};
		return *(uint32_t*)rgba.buf;
	}

	uint32_t bgra8() {
		swizzle_vec4<vec4, uint8_t, 4, 2, 1, 0, 3> rgba{
			static_cast<uint8_t>( x() * 255 ),
			static_cast<uint8_t>( y() * 255 ),
			static_cast<uint8_t>( z() * 255 ),
			static_cast<uint8_t>( w() * 255 )
		};
		return *(uint32_t*)rgba.buf;
	}

	float& x() { return buf[ 0 ]; } float x() const { return buf[ 0 ]; }
	float& r() { return x();      } float r() const { return x();      }
	float& u() { return x();      } float u() const { return x();      }

	float& y() { return buf[ 1 ]; } float y() const { return buf[ 1 ]; }
	float& g() { return y();      } float g() const { return y();      }
	float& v() { return y();      } float v() const { return y();      }

	float& z() { return buf[ 2 ]; } float z() const { return buf[ 2 ]; } 
	float& b() { return z();      } float b() const { return z();      } 

	float& w() { return buf[ 3 ]; } float w() const { return buf[ 3 ]; }
	float& a() { return w();      } float a() const { return w();      }

};

VEC_DEFAULT_OPERATORS( VEC4_OPERATOR );

union vec4i
{
	typedef int32_t Ty;

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
