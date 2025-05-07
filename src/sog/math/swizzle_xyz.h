#ifndef SOG_SWIZZLE_XYZ_H
#define SOG_SWIZZLE_XYZ_H

#include <sog/math/swizzle.h>

#define SWIZZLE_XYZ_CORE2(_a,_i) \
SWIZZLE_TYPE2(_a,_i,x,0)         \
SWIZZLE_TYPE2(_a,_i,y,1)         \
SWIZZLE_TYPE2(_a,_i,z,2)

#define SWIZZLE_XYZ_CORE3(_a,_ia, _b,_ib) \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, x,0)        \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, y,1)        \
SWIZZLE_TYPE3(_a,_ia, _b,_ib, z,2)

#define SWIZZLE_XYZ_CORE4(_a,_ia, _b,_ib, _c,_ic) \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, x,0)        \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, y,1)        \
SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, z,2)

#define SWIZZLE_XYZ_C(_a,_ia, _b,_ib)  \
SWIZZLE_XYZ_CORE3(_a,_ia, _b,_ib)      \
SWIZZLE_XYZ_CORE4(_a,_ia, _b,_ib, x,0) \
SWIZZLE_XYZ_CORE4(_a,_ia, _b,_ib, y,1) \
SWIZZLE_XYZ_CORE4(_a,_ia, _b,_ib, z,2)

#define SWIZZLE_XYZ_B(_a,_i) \
SWIZZLE_XYZ_CORE2(_a,_i)     \
SWIZZLE_XYZ_C(_a,_i,x,0)     \
SWIZZLE_XYZ_C(_a,_i,y,1)     \
SWIZZLE_XYZ_C(_a,_i,z,2)

#define SOG_SWIZZLE_XYZ \
SWIZZLE_XYZ_B(x,0)      \
SWIZZLE_XYZ_B(y,1)      \
SWIZZLE_XYZ_B(z,2)

#endif