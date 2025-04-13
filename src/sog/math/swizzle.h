#ifndef SOG_SWIZZLE_H
#define SOG_SWIZZLE_H

#define SOG_TY_TYPECAST_2(mp_x, mp_y) \
template<typename Ty, typename Mty=decltype(Ty::x), typename=decltype(Ty::y)>\
operator Ty() { return {(Mty)mp_x, (Mty)mp_y}; }

#define SOG_TY_TYPECAST_3(mp_x, mp_y, mp_z) \
template<typename Ty, typename Mty=decltype(Ty::x), typename=decltype(Ty::y), typename=decltype(Ty::y)> \
operator Ty() { return {(Mty)mp_x, (Mty)mp_y, (Mty)mp_z}; }

#define SOG_TY_TYPECAST_4(mp_x, mp_y, mp_z, mp_w) \
template<typename Ty, typename Mty=decltype(Ty::x), typename=decltype(Ty::y), typename=decltype(Ty::y), typename=decltype(Ty::y)> \
operator Ty() { return {(Mty)mp_x, (Mty)mp_y, (Mty)mp_z, (Mty)mp_w}; }

#endif