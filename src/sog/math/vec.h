#ifndef SOG_MATH_VEC_H
#define SOG_MATH_VEC_H

namespace sog {

typedef float decimal_type_t;

#define VEC_SWIZZLE2( _a, _b, ... ) \
struct { float __VA_ARGS__; \
	inline operator vec2() const { return { _a, _b }; } } \
_a##_b

#define VEC2_SWIZZLE2( _a, _b ) VEC_SWIZZLE2( _a, _b, x, y )
#define VEC3_SWIZZLE2( _a, _b ) VEC_SWIZZLE2( _a, _b, x, y, z )
#define VEC4_SWIZZLE2( _a, _b ) VEC_SWIZZLE2( _a, _b, x, y, z, w )

#define VEC_OPERATOR(_lhsTy,_rhsTy,_op,...) \
inline auto operator##_op##( const _lhsTy& _lhs, const _rhsTy& _rhs ) { \
	return __VA_ARGS__; \
}

#define VEC2_OPERATOR(_op) \
VEC_OPERATOR(vec2, decimal_type_t, _op, vec2{ _lhs.x _op _rhs,   _lhs.y _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec2, _op, vec2{ _lhs   _op _rhs.x, _lhs   _op _rhs.y } ) \
VEC_OPERATOR(vec2,           vec2, _op, vec2{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y } ) 

template<typename Ty>
union vec2_t
{
	struct { Ty x, y; };
};

typedef vec2_t<float> vec2;
typedef vec2_t<double> vec2d;

VEC2_OPERATOR( / );
VEC2_OPERATOR( * );
VEC2_OPERATOR( + );
VEC2_OPERATOR( - );

#define VEC3_OPERATOR(_op) \
VEC_OPERATOR(vec3, decimal_type_t, _op, vec3{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec3, _op, vec3{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z } ) \
VEC_OPERATOR(vec3,           vec3, _op, vec3{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z } ) 

#define VEC3_SWIZZLE2_MEMBERS \
VEC3_SWIZZLE2( x, x ); \
VEC3_SWIZZLE2( x, y ); \
VEC3_SWIZZLE2( x, z ); \
VEC3_SWIZZLE2( y, x ); \
VEC3_SWIZZLE2( y, y ); \
VEC3_SWIZZLE2( y, z ); \
VEC3_SWIZZLE2( z, x ); \
VEC3_SWIZZLE2( z, y ); \
VEC3_SWIZZLE2( z, z );

union vec3
{
	struct { float x, y, z; };

	vec3( void )                         : x{  0 }, y{  0 }, z{  0 } { };
	vec3( float _v )                     : x{ _v }, y{ _v }, z{ _v } { };
	vec3( float _x, float _y, float _z ) : x{ _x }, y{ _y }, z{ _z } { };

	VEC3_SWIZZLE2_MEMBERS;

	decimal_type_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}
};

VEC3_OPERATOR( / );
VEC3_OPERATOR( * );
VEC3_OPERATOR( + );
VEC3_OPERATOR( - );

struct vec4
{
	decimal_type_t x, y, z, w;
	vec4() = default;
	vec4( const vec3& _vec, decimal_type_t _w ) :
		x{ _vec.x }, y{ _vec.y }, z{ _vec.z }, w{ _w }
	{}
};


}



#endif
