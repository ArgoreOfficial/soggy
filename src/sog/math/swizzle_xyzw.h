#ifndef SOG_SWIZZLE_XYZWW_H
#define SOG_SWIZZLE_XYZWW_H

/**
 * member definitions.
 */

#define SOG_SWIZZLE_XYZW_TYPE2(_a,_b) \
struct _a##_b##_t {                   \
	float x, y, z, w;                 \
	operator sog::vec2();             \
} _a##_b;

#define SOG_SWIZZLE_XYZW_TYPE3(_a,_b,_c) \
struct _a##_b##_c##_t   {                \
	float x, y, z, w;                    \
	_a##_b##_c##_t() = default;          \
	_a##_b##_c##_t( const sog::vec3& p_v3 ) : x{p_v3.x}, y{p_v3.y}, z{p_v3.z} {} \
	template<typename Ty> _a##_b##_c##_t( const Ty& p_t ) : x{p_t.x}, y{p_t.y}, z{p_t.z} {} \
	operator sog::vec3();                \
} _a##_b##_c;

#define SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,_d) \
struct _a##_b##_c##_d##_t {                 \
	float x, y, z, w;                       \
	operator sog::vec4();                   \
} _a##_b##_c##_d;

#define SOG_SWIZZLE_XYZW_CORE2(_a) \
SOG_SWIZZLE_XYZW_TYPE2(_a,x)       \
SOG_SWIZZLE_XYZW_TYPE2(_a,y)       \
SOG_SWIZZLE_XYZW_TYPE2(_a,z)       \
SOG_SWIZZLE_XYZW_TYPE2(_a,w)

#define SOG_SWIZZLE_XYZW_CORE3(_a,_b) \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,x)       \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,y)       \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,z)       \
SOG_SWIZZLE_XYZW_TYPE3(_a,_b,w)

#define SOG_SWIZZLE_XYZW_CORE4(_a,_b,_c) \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,x)       \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,y)       \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,z)       \
SOG_SWIZZLE_XYZW_TYPE4(_a,_b,_c,w)

#define SOG_SWIZZLE_XYZW_C(_a,_b) \
SOG_SWIZZLE_XYZW_CORE3(_a,_b)     \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,x)   \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,y)   \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,z)   \
SOG_SWIZZLE_XYZW_CORE4(_a,_b,w)

#define SOG_SWIZZLE_XYZW_B(_a) \
SOG_SWIZZLE_XYZW_CORE2(_a)     \
SOG_SWIZZLE_XYZW_C(_a, x)      \
SOG_SWIZZLE_XYZW_C(_a, y)      \
SOG_SWIZZLE_XYZW_C(_a, z)      \
SOG_SWIZZLE_XYZW_C(_a, w)

#define SOG_SWIZZLE_XYZW \
SOG_SWIZZLE_XYZW_B(x)    \
SOG_SWIZZLE_XYZW_B(y)    \
SOG_SWIZZLE_XYZW_B(z)    \
SOG_SWIZZLE_XYZW_B(w)

/**
 * operators.
 */

 #define VEC4_OPERATOR(_op) \
 VEC_OPERATOR(sog::vec4,     float, _op, sog::vec4{ _lhs.x _op _rhs,   _lhs.y _op _rhs,   _lhs.z _op _rhs,   _lhs.w _op _rhs   } ) \
 VEC_OPERATOR(    float, sog::vec4, _op, sog::vec4{ _lhs   _op _rhs.x, _lhs   _op _rhs.y, _lhs   _op _rhs.z, _lhs   _op _rhs.w } ) \
 VEC_OPERATOR(sog::vec4, sog::vec4, _op, sog::vec4{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z, _lhs.w _op _rhs.w } ) 
 
 #define SOG_SWIZZLE_OP_XYZW_TYPE2(_a,_b) \
 sog::vec4::_a##_b##_t::operator sog::vec2() { return{ _a, _b }; }
 
 #define SOG_SWIZZLE_OP_XYZW_TYPE3(_a,_b,_c) \
 sog::vec4::_a##_b##_c##_t::operator sog::vec3() { return{ _a, _b, _c }; } 
 
 #define SOG_SWIZZLE_OP_XYZW_TYPE4(_a,_b,_c,_d) \
 sog::vec4::_a##_b##_c##_d##_t::operator sog::vec4() { return{ _a, _b, _c, _d }; }
 
 #define SOG_SWIZZLE_OP_XYZW_CORE2(_a) \
 SOG_SWIZZLE_OP_XYZW_TYPE2(_a,x)       \
 SOG_SWIZZLE_OP_XYZW_TYPE2(_a,y)       \
 SOG_SWIZZLE_OP_XYZW_TYPE2(_a,z)       \
 SOG_SWIZZLE_OP_XYZW_TYPE2(_a,w)
 
 #define SOG_SWIZZLE_OP_XYZW_CORE3(_a,_b) \
 SOG_SWIZZLE_OP_XYZW_TYPE3(_a,_b,x)       \
 SOG_SWIZZLE_OP_XYZW_TYPE3(_a,_b,y)       \
 SOG_SWIZZLE_OP_XYZW_TYPE3(_a,_b,z)       \
 SOG_SWIZZLE_OP_XYZW_TYPE3(_a,_b,w)
 
 #define SOG_SWIZZLE_OP_XYZW_CORE4(_a,_b,_c) \
 SOG_SWIZZLE_OP_XYZW_TYPE4(_a,_b,_c,x)       \
 SOG_SWIZZLE_OP_XYZW_TYPE4(_a,_b,_c,y)       \
 SOG_SWIZZLE_OP_XYZW_TYPE4(_a,_b,_c,z)       \
 SOG_SWIZZLE_OP_XYZW_TYPE4(_a,_b,_c,w)
 
 #define SOG_SWIZZLE_OP_XYZW_C(_a,_b) \
 SOG_SWIZZLE_OP_XYZW_CORE3(_a,_b)     \
 SOG_SWIZZLE_OP_XYZW_CORE4(_a,_b,x)   \
 SOG_SWIZZLE_OP_XYZW_CORE4(_a,_b,y)   \
 SOG_SWIZZLE_OP_XYZW_CORE4(_a,_b,z)   \
 SOG_SWIZZLE_OP_XYZW_CORE4(_a,_b,w)
 
 #define SOG_SWIZZLE_OP_XYZW_B(_a) \
 SOG_SWIZZLE_OP_XYZW_CORE2(_a)     \
 SOG_SWIZZLE_OP_XYZW_C(_a, x)      \
 SOG_SWIZZLE_OP_XYZW_C(_a, y)      \
 SOG_SWIZZLE_OP_XYZW_C(_a, z)      \
 SOG_SWIZZLE_OP_XYZW_C(_a, w)
 
 #define SOG_SWIZZLE_OP_XYZW \
 SOG_SWIZZLE_OP_XYZW_B( x )  \
 SOG_SWIZZLE_OP_XYZW_B( y )  \
 SOG_SWIZZLE_OP_XYZW_B( z )  \
 SOG_SWIZZLE_OP_XYZW_B( w )
 
#endif