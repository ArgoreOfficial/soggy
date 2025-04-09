#ifndef SOG_MATH_H
#define SOG_MATH_H

#include <cmath>
#include <sog/math/vec.h>

namespace sog {

template<typename Ty>
Ty clamp( const Ty& _v, const Ty& _min, const Ty& _max )
{
	const Ty t = _v < _min ? _min : _v;
	return t > _max ? _max : t;
}

decimal_type_t length( const vec2& _vec2 ) {
	return std::sqrt( _vec2.x * _vec2.x + _vec2.y * _vec2.y );
}

vec2 floor( const sog::vec2& _t ) {
	return sog::vec2{
		std::floor( _t.x ),
		std::floor( _t.y )
	};
}

vec2 mod( const vec2& _x, decimal_type_t _y ) {
	return _x - _y * floor( _x / _y );
}

}

#endif
