#ifndef SOG_VECTOR2_H
#define SOG_VECTOR2_H

#include <sog/math/vec_core.h>

namespace sog {

#define VEC2_OPERATOR(_op) \
VEC_OPERATOR(vec2<Ty>, decimal_type_t, _op, vec2<Ty>{ _lhs.x _op _rhs,   _lhs.y _op _rhs   } ) \
VEC_OPERATOR(decimal_type_t, vec2<Ty>, _op, vec2<Ty>{ _lhs   _op _rhs.x, _lhs   _op _rhs.y } ) \
VEC_OPERATOR(vec2<Ty>,       vec2<Ty>, _op, vec2<Ty>{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y } ) 

#define SWIZZLE_XY_MEMBERS \
SWIZZLE_2_XY( x, x, Ty ); \
SWIZZLE_2_XY( x, y, Ty ); \
SWIZZLE_2_XY( y, x, Ty ); \
SWIZZLE_2_XY( y, y, Ty );

template<typename Ty>
union vec2
{
	struct { Ty x, y; };

	vec2() : x{ 0 }, y{ 0 } {}
	vec2( Ty _x, Ty _y ) : x{ _x }, y{ _y } {}
};

typedef vec2<float>  vec2f;
typedef vec2<double> vec2d;

VEC_DEFAULT_OPERATORS( VEC2_OPERATOR );

}

#endif
