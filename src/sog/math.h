#ifndef SOG_MATH_H
#define SOG_MATH_H

#include <stdint.h>
#include <algorithm>
#include <cmath>

#include <sog/math/vector2.h>
#include <sog/math/vector3.h>
#include <sog/math/vector4.h>

#define GEN_STD_DEF(_f)  inline float _f( const float& _x ) { return std::_f( _x ); }
#define VEC2_STD_DEF(_f) inline vec2 _f( const vec2& _v ) { return { std::_f( _v.x ), std::_f( _v.y ) }; }
#define VEC3_STD_DEF(_f) inline vec3 _f( const vec3& _v ) { return { std::_f( _v.x ), std::_f( _v.y ), std::_f( _v.z ) }; }
#define VEC4_STD_DEF(_f) inline vec4 _f( const vec4& _v ) { return { std::_f( _v.x ), std::_f( _v.y ), std::_f( _v.z ), std::_f( _v.w ) }; }

#define SOG_STD_DEF(_f) \
GEN_STD_DEF( _f ); \
VEC2_STD_DEF( _f ); \
VEC3_STD_DEF( _f ); \
VEC4_STD_DEF( _f );

#define VEC_GENERIC(_func, ...) \
inline float _func( const float& _x ) { return __VA_ARGS__; } \
inline vec2 _func( const vec2& _x ) { return __VA_ARGS__; } \
inline vec3 _func( const vec3& _x ) { return __VA_ARGS__; } \
inline vec4 _func( const vec4& _x ) { return __VA_ARGS__; } 

namespace sog {

SOG_STD_DEF( abs );
SOG_STD_DEF( floor );
SOG_STD_DEF( sin );
SOG_STD_DEF( cos );
SOG_STD_DEF( tanh );

VEC_GENERIC( fract, _x - floor( _x ) );

template<typename Ty>
inline Ty clamp( const Ty& _v, const Ty& _min, const Ty& _max )
{
	const Ty t = _v < _min ? _min : _v;
	return t > _max ? _max : t;
}

inline float length( const vec2& _vec2 ) {
	return std::sqrt( _vec2.x * _vec2.x + _vec2.y * _vec2.y );
}

inline vec2 mod( const vec2& _x, float _y ) {
	return _x - _y * floor( _x / _y );
}

inline float dot( const vec3& _a, const vec3& _b ) {
	return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

template<typename Ty>
inline Ty min( Ty p_a, Ty p_b ) {
	return std::min<Ty>( p_a, p_b );
}

template<typename Ty, typename... Args>
inline Ty min( Ty p_a, Ty p_b, Args... p_args ) {
	return sog::min<Ty>( p_a, sog::min<Ty>( p_b, p_args... ) );
}

template<typename Ty>
inline Ty max( Ty p_a, Ty p_b ) {
	return std::max<Ty>( p_a, p_b );
}

template<typename Ty, typename... Args>
inline Ty max( Ty p_a, Ty p_b, Args... p_args ) {
	return sog::max<Ty>( p_a, sog::max<Ty>( p_b, p_args... ) );
}

}

#endif
