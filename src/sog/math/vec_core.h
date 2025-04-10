#ifndef SOG_MATH_VEC_CORE_H
#define SOG_MATH_VEC_CORE_H

namespace sog {

typedef float decimal_type_t;

}

#define VEC_OPERATOR(_lhsTy,_rhsTy,_op,...) \
inline auto operator##_op##( const _lhsTy& _lhs, const _rhsTy& _rhs ) { \
	return __VA_ARGS__; \
}

#define VEC_DEFAULT_OPERATORS(_m) _m( / ); _m( * ); _m( + ); _m( - );

#endif
