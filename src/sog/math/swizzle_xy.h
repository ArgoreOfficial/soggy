#ifndef SOG_SWIZZLE_XY_H
#define SOG_SWIZZLE_XY_H

#include <sog/math/swizzle.h>

#define SWIZZLE_XY_CORE2(_a,_i) \
SWIZZLE_TYPE2(_a,_i,x,0)        \
SWIZZLE_TYPE2(_a,_i,y,1)

#define SWIZZLE_XY_CORE3(_a,_ia, _b,_ib) \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, x,0)       \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, y,1)

#define SWIZZLE_XY_CORE4(_a,_ia, _b,_ib, _c,_ic) \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, x,0)       \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, y,1)

#define SWIZZLE_XY_C(_a,_ia, _b,_ib)  \
SWIZZLE_XY_CORE3(_a,_ia, _b,_ib)      \
SWIZZLE_XY_CORE4(_a,_ia, _b,_ib, x,0) \
SWIZZLE_XY_CORE4(_a,_ia, _b,_ib, y,1)

#define SWIZZLE_XY_B(_a,_i) \
SWIZZLE_XY_CORE2(_a,_i)     \
SWIZZLE_XY_C(_a,_i,x,0)     \
SWIZZLE_XY_C(_a,_i,y,1)

#define SOG_SWIZZLE_XY \
SWIZZLE_XY_B(x,0)      \
SWIZZLE_XY_B(y,1)

#endif