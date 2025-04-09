#ifndef SOG_MATH_H
#define SOG_MATH_H

#include <cmath>
#include <sog/math/vector2.h>
#include <sog/math/vector3.h>
#include <sog/math/vector4.h>

#define GEN_STD_DEF(_f) inline decimal_type_t _f( const decimal_type_t& _x ) { return std::_f( _x ); }
#define VEC2_STD_DEF(_f) template<typename Ty> inline vec2<Ty> _f( const vec2<Ty>& _v ) { return { std::_f( _v.x ), std::_f( _v.y ) }; }
#define VEC3_STD_DEF(_f) template<typename Ty> inline vec3<Ty> _f( const vec3<Ty>& _v ) { return { std::_f( _v.x ), std::_f( _v.y ), std::_f( _v.z ) }; }
#define VEC4_STD_DEF(_f) template<typename Ty> inline vec4<Ty> _f( const vec4<Ty>& _v ) { return { std::_f( _v.x ), std::_f( _v.y ), std::_f( _v.z ), std::_f( _v.w ) }; }

#define SOG_STD_DEF(_f) \
GEN_STD_DEF( _f ); \
VEC2_STD_DEF( _f ); \
VEC3_STD_DEF( _f ); \
VEC4_STD_DEF( _f );

#define VEC_GENERIC(_func, ...) \
inline decimal_type_t _func( const decimal_type_t& _x ) { return __VA_ARGS__; } \
template<typename Ty> inline vec2<Ty> _func( const vec2<Ty>& _x ) { return __VA_ARGS__; } \
template<typename Ty> inline vec3<Ty> _func( const vec3<Ty>& _x ) { return __VA_ARGS__; } \
template<typename Ty> inline vec4<Ty> _func( const vec4<Ty>& _x ) { return __VA_ARGS__; } 

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

inline decimal_type_t length( const vec2f& _vec2 ) {
	return std::sqrt( _vec2.x * _vec2.x + _vec2.y * _vec2.y );
}

inline vec2f mod( const vec2f& _x, decimal_type_t _y ) {
	return _x - _y * floor( _x / _y );
}

inline decimal_type_t dot( const vec3f& _a, const vec3f& _b ) {
	return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z;
}

}

#endif
