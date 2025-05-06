/**
 * @file main.cpp
 * @author Argore
 * @brief Basic xmake C++ Project Template
 * @version 0.1
 * @date 2025-04-04
 * 
 * @copyright Copyright (c) 2025 Argore
 * 
 */

#include <stdio.h>
#include <chrono>

#include <sog/context.h>
#include <sog/math.h>
#include <sog/kernel.h>
#include <sog/graphics.h>

#include <sog/math/swizzle.h>

#include <math.h>

#include <thread>

#define SDL_MAIN_HANDLED
#include <SDL.h>

sog::Context context;
float g_time = 0.0f;
sog::vec2 iResolution{};

// https://www.shadertoy.com/view/XsXXDn
void shaderCreation( sog::vec4& _outFragColor, sog::vec2 _fragCoord )
{
	sog::vec2 r = sog::vec2{ (float)context.width, (float)context.height };

	sog::vec3 c;
	float l, z = g_time;
	for ( int i = 0; i < 3; i++ )
	{
		sog::vec2 uv, p = _fragCoord / r;
		uv = p;
		p = p - 0.5f;
		p.x *= r.x / r.y;
		z += 0.07f;
		l = std::max( sog::length( p ), 0.0000001f );
		uv = uv + ( p / l * ( sin( z ) + 1.0f ) * abs( sin( l * 9.0f - z - z ) ) );
		c[ i ] = 0.01f / sog::length( sog::mod( uv, 1.0f ) - 0.5f );
	}
	
	_outFragColor = sog::vec4( c / l, g_time );
}

struct FramerateCounter
{
	FramerateCounter() {
		start = timer.now();
	}

	void tick() {
		auto stop = timer.now();
		frametime = std::chrono::duration_cast<std::chrono::microseconds>( stop - start ).count() / 1000.0;
		
		frametimeBuffer.push_back( frametime );
		clock += frametime;

		if( clock - frametimeCountdown > 300 )
		{
			if( !frametimeBuffer.empty() )
			{
				double accum = 0.0;
				for( auto d : frametimeBuffer )
					accum += d;
				accum /= frametimeBuffer.size();

				frametimeCountdown = clock;
				frametimeBuffer.clear();

				averageFrametime = accum;
			}
		}

		start = timer.now();
	}

	double getDeltaTime() {
		return frametime / 1000.0;
	}

	double getAverageDeltaTime() {
		return averageFrametime / 1000.0;
	}

	// in seconds
	double getClock() {
		return clock / 1000.0;
	}

	std::chrono::steady_clock::time_point start{};
	std::chrono::steady_clock::time_point end{};

	std::vector<double> frametimeBuffer{};
	double frametimeCountdown = 0.0;

	// in milliseconds
	double clock = 0.0;
	double frametime        = 1.0 / 60.0;
	double averageFrametime = 1.0 / 60.0;

	std::chrono::high_resolution_clock timer;
};


inline uint32_t xyToBufferOffset( uint32_t p_x, uint32_t p_y, uint32_t p_width ) 
{
	return p_y * p_width + p_x;
}

/*
plotLineLow(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
	dx = x1 - x0
	dy = y1 - y0
	yi = 1
	if dy < 0
		yi = -1
		dy = -dy
	end if
	D = (2 * dy) - dx
	y = y0

	for x from x0 to x1
		plot(x, y)
		if D > 0
			y = y + yi
			D = D + (2 * (dy - dx))
		else
			D = D + 2*dy
		end if
}

void plotLineHigh(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
	int32_t dx = x1 - x0;
	int32_t dy = y1 - y0;
	int32_t xi = 1;
	if ( dx < 0 ) {
		xi = -1;
		dx = -dx;
	}
	int32_t D = (2 * dx) - dy;
	int32_t x = x0;

	for ( int32_t y = y0; y <= y1; y++ ) {
		//plot(x, y)
		if ( D > 0 ) {
			x = x + xi;
			D = D + (2 * dx - dy));
		} else {
			D = D + 2*dx;
		}
	}
}
*/

inline double sinn( double _x ) { return sin( _x ) * 0.5 + 0.5; }
inline double cosn( double _x ) { return cos( _x ) * 0.5 + 0.5; }

inline float sinfn( float _x ) { return sinf( _x ) * 0.5f + 0.5f; }
inline float cosfn( float _x ) { return cosf( _x ) * 0.5f + 0.5f; }

sog::vec2 UVs[]{
	{0,0},
	{1,0},
	{1,1}
};

template<typename Ty>
Ty lerp( Ty a, Ty b, float t ) { return a + t * ( b - a ); }

static int raster_shader( sog::vec4& p_out, int32_t p_bary0, int32_t p_bary1, int32_t p_bary2 ) 
{
	float total = p_bary0 + p_bary1 + p_bary2;
	if ( total == 0 )
		return 0; // discard
	
	sog::vec3 bary = sog::vec3{ (float)p_bary0, (float)p_bary1, (float)p_bary2 } / total;

	sog::vec2 uv = lerp( UVs[ 0 ], UVs[ 1 ], bary.y );
	uv = lerp( uv, UVs[ 2 ], bary.z );

	p_out = sog::vec4( uv.x, uv.y, 0, 1 );
	return 1;
}



// new swizzle



template<size_t Comp>
struct swizzle_scalar
{
	float buf[ 1 ];

	float& operator=( const float _v ) {
		buf[ Comp ] = _v;
		return buf[ Comp ];
	}
	
	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	operator float() const { return buf[ Comp ]; }
	
	float operator++( int ) { return buf[ Comp ]++; }
	float operator++()      { return ++buf[ Comp ]; }
	float operator--( int ) { return buf[ Comp ]--; }
	float operator--()      { return --buf[ Comp ]; }
};

template<typename VecTy, size_t Size, size_t Comp1, size_t Comp2>
struct swizzle_vec2
{
	float buf[ Size ];

	swizzle_vec2( void ) = default;
		
	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

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

template<typename VecTy, size_t Size, size_t Comp1, size_t Comp2, size_t Comp3>
struct swizzle_vec3
{
	float buf[ Size ];

	swizzle_vec3( void ) = default;
	swizzle_vec3( const float _x, const float _y, const float _z ) { 
		buf[ Comp1 ] = _x; 
		buf[ Comp2 ] = _y; 
		buf[ Comp3 ] = _z; 
	}

	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

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

template<typename VecTy, size_t Size, size_t Comp1, size_t Comp2, size_t Comp3, size_t Comp4>
struct swizzle_vec4
{
	float buf[ Size ];

	swizzle_vec4( void ) = default;
	swizzle_vec4( const float _x, const float _y, const float _z, const float _w ) {
		buf[ Comp1 ] = _x;
		buf[ Comp2 ] = _y;
		buf[ Comp3 ] = _z;
		buf[ Comp4 ] = _w;
	}

	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

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

struct tvec2;
struct tvec3;
struct tvec4;

#define SWIZZLE_XY_TYPE2(_a,_ia, _b,_ib                ) swizzle_vec2<tvec2, SIZE, _ia, _ib> _a##_b;
#define SWIZZLE_XY_TYPE3(_a,_ia, _b,_ib, _c,_ic        ) swizzle_vec3<tvec3, SIZE, _ia, _ib, _ic> _a##_b##_c;
#define SWIZZLE_XY_TYPE4(_a,_ia, _b,_ib, _c,_ic, _d,_id) swizzle_vec4<tvec4, SIZE, _ia, _ib, _ic, _id> _a##_b##_c##_d;

#define SWIZZLE_XY_CORE2(_a,_i) \
SWIZZLE_XY_TYPE2(_a,_i,x,0)     \
SWIZZLE_XY_TYPE2(_a,_i,y,1)

#define SWIZZLE_XY_CORE3(_a,_ia, _b,_ib) \
SWIZZLE_XY_TYPE3(_a,_ia, _b,_ib, x,0)    \
SWIZZLE_XY_TYPE3(_a,_ia, _b,_ib, y,1)

#define SWIZZLE_XY_CORE4(_a,_ia, _b,_ib, _c,_ic) \
SWIZZLE_XY_TYPE4(_a,_ia, _b,_ib, _c,_ic, x,0)    \
SWIZZLE_XY_TYPE4(_a,_ia, _b,_ib, _c,_ic, y,1)

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


struct tvec2
{
	static constexpr size_t SIZE = 2;

	tvec2() = default;
	
	template<typename Ty> tvec2( const Ty& _x, const Ty& _y ) { 
		buf[ 0 ] = static_cast<float>( _x );
		buf[ 1 ] = static_cast<float>( _y );
	}
	
	template<typename Ty> tvec2( const Ty& _v ) {
		buf[ 0 ] = static_cast<float>( _v );
		buf[ 1 ] = static_cast<float>( _v );
	}

	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	union
	{
		float buf[ 2 ] = { 0.0f, 0.0f };
	
		swizzle_scalar<0> x, r, u;
		swizzle_scalar<1> y, g, v;
		
		SOG_SWIZZLE_XY;

	};
};

struct tvec3
{
	static constexpr size_t SIZE = 3;

	tvec3() = default;

	template<typename Ty> tvec3( const Ty& _x, const Ty& _y, const Ty& _z ) : xyz{ static_cast<float>( _x ), static_cast<float>( _y ), static_cast<float>( _z ) } {}
	template<typename Ty> tvec3( const float& _v )                          : xyz{ _v, _v, _v } { }

	float& operator[]( const size_t _idx )       { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	union
	{
		float buf[ SIZE ] = { 0.0f, 0.0f, 0.0f };

		swizzle_scalar<0> x, r, u;
		swizzle_scalar<1> y, g, v;
		swizzle_scalar<2> z, b;

		swizzle_vec2<tvec2, SIZE, 0, 0> xx;
		swizzle_vec2<tvec2, SIZE, 0, 1> xy;
		swizzle_vec2<tvec2, SIZE, 1, 0> yx;
		swizzle_vec2<tvec2, SIZE, 1, 1> yy;

		swizzle_vec2<tvec2, SIZE, 0, 2> xz;

		swizzle_vec3<tvec3, SIZE, 0, 1, 2> xyz;
	};
};

struct tvec4
{
	static constexpr size_t SIZE = 4;

	tvec4() = default;

	template<typename Ty> tvec4( const float _x, const float _y, const float _z, const float _w ) 	
	{
		buf[ 0 ] = _x;
		buf[ 1 ] = _y;
		buf[ 2 ] = _z;
		buf[ 3 ] = _w;
	}

	template<typename Ty> tvec4( const float& _v ) {
		buf[ 0 ] = _v;
		buf[ 1 ] = _v;
		buf[ 2 ] = _v;
		buf[ 3 ] = _v;
	}

	float& operator[]( const size_t _idx ) { return buf[ _idx ]; }
	float  operator[]( const size_t _idx ) const { return buf[ _idx ]; }

	union
	{
		float buf[ SIZE ] = { 0.0f, 0.0f, 0.0f };

		swizzle_scalar<0> x, r, u;
		swizzle_scalar<1> y, g, v;
		swizzle_scalar<2> z, b;
		swizzle_scalar<3> w, a;
	};
};



int main( int argc, char* argv[] )
{
	context = sog::initializeContext( 720, 480 );
	iResolution = { (float)context.width, (float)context.height };

    sog::swapBuffers( &context );
    
	const uint32_t size = (720 * 480) / ( std::thread::hardware_concurrency() - 1 );
	sog::KernelList kernels = sog::buildKernelList( &context, size );

    int quit = 0;
    SDL_Event event;

	tvec2 test1{ 5.0f, 2.0f };
	
	tvec3 test2{ 3,4,3 }; // 3 1 3 
	test2.xz = test2.yy;  // 4 4 4
	test2.x = 3;          // 3 4 4

	tvec3 test3{};
	test3 = test1.xxx;

	FramerateCounter ftcounter{};

    while( !quit )
    {
		ftcounter.tick();
		g_time = ftcounter.getClock();

		while ( SDL_PollEvent( &event ) )
			quit |= ( event.type == SDL_QUIT );
		
		sog::gfx::clear( &context, sog::vec4(0,0,0,1).bgra8 );

		// sog::gfx::runShader( &kernels, shaderCreation );

		sog::vec4 base{ 0.0f, 16.0f, 16.0f, 0.0f };
		base += { 0.0f, sinf( g_time ) * 64.0f, cosf( g_time ) * 64.0f, 0.0f };

		sog::vec2 point_0 = base.yz;
		sog::vec2 point_1{ 300.0f, 200.0f };
		sog::vec2 point_2{ 150, 400 };
		
		sog::beginDraw( &context );
		uint32_t* pixels = (uint32_t*)context.pBackBuffer->pixels;

		sog::gfx::raster_triangle( raster_shader, pixels, context.width, context.height, point_0, point_1, point_2 );

		sog::endDraw( &context );

        std::string title = "Soggy!";
        title += "  FPS:" + std::to_string( 1.0 / ftcounter.getAverageDeltaTime() );
        title += "  FT:" + std::to_string( ftcounter.getAverageDeltaTime() );
        SDL_SetWindowTitle( context.pWindow, title.c_str() );

		sog::swapBuffers( &context );
	}

	sog::shutdownContext( &context );

    return 0;
}
