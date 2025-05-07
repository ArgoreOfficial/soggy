#ifndef SOG_SWIZZLE_XYZWW_H
#define SOG_SWIZZLE_XYZWW_H

#include <sog/math/swizzle.h>

#define SWIZZLE_XYZW_CORE2(_a,_i) \
SWIZZLE_TYPE2(_a,_i,x,0)          \
SWIZZLE_TYPE2(_a,_i,y,1)          \
SWIZZLE_TYPE2(_a,_i,z,2)          \
SWIZZLE_TYPE2(_a,_i,w,3)

#define SWIZZLE_XYZW_CORE3(_a,_ia, _b,_ib) \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, x,0)         \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, y,1)         \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, z,2)         \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, w,3)

#define SWIZZLE_XYZW_CORE4(_a,_ia, _b,_ib, _c,_ic) \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, x,0)         \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, y,1)         \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, z,2)         \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, w,3)

#define SWIZZLE_XYZW_C(_a,_ia, _b,_ib)  \
SWIZZLE_XYZW_CORE3(_a,_ia, _b,_ib)      \
SWIZZLE_XYZW_CORE4(_a,_ia, _b,_ib, x,0) \
SWIZZLE_XYZW_CORE4(_a,_ia, _b,_ib, y,1) \
SWIZZLE_XYZW_CORE4(_a,_ia, _b,_ib, z,2) \
SWIZZLE_XYZW_CORE4(_a,_ia, _b,_ib, w,3)

#define SWIZZLE_XYZW_B(_a,_i) \
SWIZZLE_XYZW_CORE2(_a,_i)     \
SWIZZLE_XYZW_C(_a,_i,x,0)     \
SWIZZLE_XYZW_C(_a,_i,y,1)     \
SWIZZLE_XYZW_C(_a,_i,z,2)     \
SWIZZLE_XYZW_C(_a,_i,w,3)

#define SOG_SWIZZLE_XYZW \
SWIZZLE_XYZW_B(x,0)     \
SWIZZLE_XYZW_B(y,1)     \
SWIZZLE_XYZW_B(z,2)     \
SWIZZLE_XYZW_B(w,3)


#endif