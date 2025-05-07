#ifndef SOG_VECTOR2_H
#define SOG_VECTOR2_H

#include <sog/math/vec_core.h>

#define SOG_ENABLE_SWIZZLE_XY
#include <sog/math/swizzle_xy.h>

namespace sog {

#define VEC2_OPERATOR(_op) \
VEC_OPERATOR( vec2, float, _op, vec2{ _lhs.x() _op _rhs,     _lhs.y() _op _rhs     } ) \
VEC_OPERATOR(float,  vec2, _op, vec2{ _lhs     _op _rhs.x(), _lhs     _op _rhs.y() } ) \
VEC_OPERATOR( vec2,  vec2, _op, vec2{ _lhs.x() _op _rhs.x(), _lhs.y() _op _rhs.y() } ) 

#define VEC2i_OPERATOR(_op) \
VEC_OPERATOR(  vec2i, int32_t, _op, vec2i{ _lhs.x() _op _rhs,     _lhs.y() _op _rhs     } ) \
VEC_OPERATOR(int32_t,   vec2i, _op, vec2i{ _lhs     _op _rhs.x(), _lhs     _op _rhs.y() } ) \
VEC_OPERATOR(  vec2i,   vec2i, _op, vec2i{ _lhs.x() _op _rhs.x(), _lhs.y() _op _rhs.y() } ) 

struct vec2
{
	typedef float Ty;
	static constexpr size_t SIZE = 2;

	union
	{
		float buf[ SIZE ] = { 0.0f }; // TODO: __m64 for x86 platforms
		SOG_SWIZZLE_XY;
	};

	vec2() = default;
	
	vec2( const float& _x, const float& _y ) : xy{ _x, _y } {}
	vec2( const float& _v )                  : xy{ _v, _v } {}

	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }
	
	float& x() { return buf[ 0 ]; } float x() const { return buf[ 0 ]; }
	float& r() { return x();      } float r() const { return x();      }
	float& u() { return x();      } float u() const { return x();      }

	float& y() { return buf[ 1 ]; } float y() const { return buf[ 1 ]; }
	float& g() { return y();      } float g() const { return y();      }
	float& v() { return y();      } float v() const { return y();      }

};

struct vec2i
{
	typedef int32_t Ty;
	static constexpr size_t SIZE = 2;

	union
	{
		int32_t buf[ SIZE ] = { 0 }; // TODO: __m64 for x86 platforms
		SOG_SWIZZLE_XY;
	};

	vec2i() = default;

	vec2i( const int32_t& _x, const int32_t& _y ) : xy{ _x, _y } { }
	vec2i( const int32_t& _v )                    : xy{ _v, _v } { }
	vec2i( const sog::vec2& p_v2 ) : 
		xy{ 
			static_cast<int32_t>( p_v2.x() ), 
			static_cast<int32_t>( p_v2.y() ) 
		} 
	{ }

	int32_t& operator[]( const size_t _idx ) { return buf[ _idx ]; }
	int32_t  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	int32_t& x() { return buf[ 0 ]; }
	int32_t& r() { return x(); }
	int32_t& u() { return x(); }

	int32_t& y() { return buf[ 1 ]; }
	int32_t& g() { return y(); }
	int32_t& v() { return y(); }

};

VEC_DEFAULT_OPERATORS( VEC2_OPERATOR );
//VEC_DEFAULT_OPERATORS( VEC2i_OPERATOR );

}

#endif
