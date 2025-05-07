#ifndef SOG_SWIZZLE_H
#define SOG_SWIZZLE_H

template<typename Ty, size_t Comp>
struct swizzle_scalar // remove?
{
	Ty buf[ 1 ];

	Ty& operator=( const Ty _v ) {
		buf[ Comp ] = _v;
		return buf[ Comp ];
	}

	Ty& operator[]( const size_t _idx ) { return buf[ _idx ]; }
	Ty  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	operator Ty() const { return buf[ Comp ]; }

	Ty operator++( int ) { return   buf[ Comp ]++; }
	Ty operator++()      { return ++buf[ Comp ]; }
	Ty operator--( int ) { return   buf[ Comp ]--; }
	Ty operator--()      { return --buf[ Comp ]; }

	template<typename Oty> Oty operator +( const Oty& _rhs ) { return buf[ Comp ] + _rhs; }
	template<typename Oty> Oty operator -( const Oty& _rhs ) { return buf[ Comp ] - _rhs; }
	template<typename Oty> Oty operator *( const Oty& _rhs ) { return buf[ Comp ] * _rhs; }

	template<typename Oty> Oty& operator +=( const Oty& _rhs ) { return buf[ Comp ] += _rhs; }
	template<typename Oty> Oty& operator -=( const Oty& _rhs ) { return buf[ Comp ] -= _rhs; }
	template<typename Oty> Oty& operator *=( const Oty& _rhs ) { return buf[ Comp ] *= _rhs; }
};

template<typename VecTy, typename Ty, size_t Size, size_t Comp1, size_t Comp2>
struct swizzle_vec2
{
	Ty buf[ Size ];

	swizzle_vec2( void ) = default;
	swizzle_vec2( const Ty _comp0, const Ty _comp1 ) {
		buf[ Comp1 ] = _comp0;
		buf[ Comp2 ] = _comp1;
	}

	Ty& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	Ty  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	inline operator VecTy() {
		VecTy t{};
		t[ 0 ] = buf[ Comp1 ];
		t[ 1 ] = buf[ Comp2 ];
		return t;
	}

	inline VecTy operator=( const VecTy& _vec ) {
		buf[ Comp1 ] = _vec[ 0 ];
		buf[ Comp2 ] = _vec[ 1 ];
		return _vec;
	}

};

template<typename VecTy, typename Ty, size_t Size, size_t Comp1, size_t Comp2, size_t Comp3>
struct swizzle_vec3
{
	Ty buf[ Size ];

	swizzle_vec3( void ) = default;
	swizzle_vec3( const Ty _x, const Ty _y, const Ty _z ) {
		buf[ Comp1 ] = _x;
		buf[ Comp2 ] = _y;
		buf[ Comp3 ] = _z;
	}

	Ty& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	Ty  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	inline operator VecTy() {
		VecTy t{};
		t[ 0 ] = buf[ Comp1 ];
		t[ 1 ] = buf[ Comp2 ];
		t[ 2 ] = buf[ Comp3 ];
		return t;
	}

	inline VecTy operator=( const VecTy& _vec ) {
		return VecTy{
			buf[ Comp1 ] = _vec.x,
			buf[ Comp2 ] = _vec.y,
			buf[ Comp3 ] = _vec.z
		};
	}
};

template<typename VecTy, typename Ty, size_t Size, size_t Comp1, size_t Comp2, size_t Comp3, size_t Comp4>
struct swizzle_vec4
{
	Ty buf[ Size ];

	swizzle_vec4( void ) = default;
	swizzle_vec4( const Ty _x, const Ty _y, const Ty _z, const Ty _w ) {
		buf[ Comp1 ] = _x;
		buf[ Comp2 ] = _y;
		buf[ Comp3 ] = _z;
		buf[ Comp4 ] = _w;
	}

	Ty& operator[]( const size_t _idx ) { return buf[ _idx ]; }
	Ty  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	inline operator VecTy() {
		VecTy t{};
		t[ 0 ] = buf[ Comp1 ];
		t[ 1 ] = buf[ Comp2 ];
		t[ 2 ] = buf[ Comp3 ];
		t[ 3 ] = buf[ Comp4 ];
		return t;
	}

	inline VecTy operator=( const VecTy& _vec ) {
		return VecTy{
			buf[ Comp1 ] = _vec.x,
			buf[ Comp2 ] = _vec.y,
			buf[ Comp3 ] = _vec.z,
			buf[ Comp4 ] = _vec.w
		};
	}
};

#define SWIZZLE_TYPE2(_a,_ia, _b,_ib                ) swizzle_vec2<vec2, Ty, SIZE, _ia, _ib>           _a##_b;
#define SWIZZLE_TYPE3(_a,_ia, _b,_ib, _c,_ic        ) swizzle_vec3<vec3, Ty, SIZE, _ia, _ib, _ic>      _a##_b##_c;
#define SWIZZLE_TYPE4(_a,_ia, _b,_ib, _c,_ic, _d,_id) swizzle_vec4<vec4, Ty, SIZE, _ia, _ib, _ic, _id> _a##_b##_c##_d;

#endif