#ifndef SOG_MATH_VEC_CORE_H
#define SOG_MATH_VEC_CORE_H

#include <immintrin.h>
#include <stdint.h>

#define VEC_OPERATOR(_lhsTy,_rhsTy,_op,...) \
inline auto operator##_op##( const _lhsTy& _lhs, const _rhsTy& _rhs ) { \
	return __VA_ARGS__; \
}

#define VEC_DEFAULT_OPERATORS(_m) _m( / ); _m( * ); _m( + ); _m( - );

namespace sog {

struct vec2;
struct vec3;
struct vec4;

}

#endif
