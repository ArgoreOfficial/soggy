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

struct Viewport
{
	int32_t width = 1920;
	int32_t height = 1061;
};

struct Range
{
	float start;
	float end;
};

constexpr float mapRange( float _v, float _fromStart, float _fromEnd, float _toStart, float _toEnd ) {
	double slope = ( _toEnd - _toStart ) / ( _fromEnd - _fromStart );
	return _toStart + slope * ( _v - _fromStart );
}

float mapRange( float _v, const Range& _from, const Range& _to ) {
	return mapRange( _v, _from.start, _from.end, _to.start, _to.end );
}

union bikeshed_vec3
{
	struct { float x, y, z; };
	
	SOG_SWIZZLE_XYZ;
};

constexpr void swizzleCompletenessTestVec3()
{
	bikeshed_vec3 v3;
	// 1 comp
	(void)v3.x;
	(void)v3.y;
	(void)v3.z;
	// 2 comp
	(void)v3.xx;
	(void)v3.xy;
	(void)v3.xz;
	(void)v3.yx;
	(void)v3.yy;
	(void)v3.yz;
	(void)v3.zx;
	(void)v3.zy;
	(void)v3.zz;
	// 3 comp
	(void)v3.xxx;
	(void)v3.xxy;
	(void)v3.xxz;
	(void)v3.xyx;
	(void)v3.xyy;
	(void)v3.xyz;
	(void)v3.xzx;
	(void)v3.xzy;
	(void)v3.xzz;
	(void)v3.yxx;
	(void)v3.yxy;
	(void)v3.yxz;
	(void)v3.yyx;
	(void)v3.yyy;
	(void)v3.yyz;
	(void)v3.yzx;
	(void)v3.yzy;
	(void)v3.yzz;
	(void)v3.zxx;
	(void)v3.zxy;
	(void)v3.zxz;
	(void)v3.zyx;
	(void)v3.zyy;
	(void)v3.zyz;
	(void)v3.zzx;
	(void)v3.zzy;
	(void)v3.zzz;
	// 4 comp
	(void)v3.xxxx;
	(void)v3.xxxy;
	(void)v3.xxxz;
	(void)v3.xxyx;
	(void)v3.xxyy;
	(void)v3.xxyz;
	(void)v3.xxzx;
	(void)v3.xxzy;
	(void)v3.xxzz;
	(void)v3.xyxx;
	(void)v3.xyxy;
	(void)v3.xyxz;
	(void)v3.xyyx;
	(void)v3.xyyy;
	(void)v3.xyyz;
	(void)v3.xyzx;
	(void)v3.xyzy;
	(void)v3.xyzz;
	(void)v3.xzxx;
	(void)v3.xzxy;
	(void)v3.xzxz;
	(void)v3.xzyx;
	(void)v3.xzyy;
	(void)v3.xzyz;
	(void)v3.xzzx;
	(void)v3.xzzy;
	(void)v3.xzzz;
	(void)v3.yxxx;
	(void)v3.yxxy;
	(void)v3.yxxz;
	(void)v3.yxyx;
	(void)v3.yxyy;
	(void)v3.yxyz;
	(void)v3.yxzx;
	(void)v3.yxzy;
	(void)v3.yxzz;
	(void)v3.yyxx;
	(void)v3.yyxy;
	(void)v3.yyxz;
	(void)v3.yyyx;
	(void)v3.yyyy;
	(void)v3.yyyz;
	(void)v3.yyzx;
	(void)v3.yyzy;
	(void)v3.yyzz;
	(void)v3.yzxx;
	(void)v3.yzxy;
	(void)v3.yzxz;
	(void)v3.yzyx;
	(void)v3.yzyy;
	(void)v3.yzyz;
	(void)v3.yzzx;
	(void)v3.yzzy;
	(void)v3.yzzz;
	(void)v3.zxxx;
	(void)v3.zxxy;
	(void)v3.zxxz;
	(void)v3.zxyx;
	(void)v3.zxyy;
	(void)v3.zxyz;
	(void)v3.zxzx;
	(void)v3.zxzy;
	(void)v3.zxzz;
	(void)v3.zyxx;
	(void)v3.zyxy;
	(void)v3.zyxz;
	(void)v3.zyyx;
	(void)v3.zyyy;
	(void)v3.zyyz;
	(void)v3.zyzx;
	(void)v3.zyzy;
	(void)v3.zyzz;
	(void)v3.zzxx;
	(void)v3.zzxy;
	(void)v3.zzxz;
	(void)v3.zzyx;
	(void)v3.zzyy;
	(void)v3.zzyz;
	(void)v3.zzzx;
	(void)v3.zzzy;
	(void)v3.zzzz;
}

int main( int argc, char* argv[] )
{
	context = sog::initializeContext( 720, 480 );
	iResolution = { (float)context.width, (float)context.height };

	constexpr float v = mapRange( 0.5f, 0, 1, -1, 1 );

    sog::swapBuffers( &context );
    sog::gfx::clear( &context, 255, 0, 255, 255 );

	const uint32_t size = (720 * 480) / ( std::thread::hardware_concurrency() - 1 );
	sog::KernelList kernels = sog::buildKernelList( &context, size );

    int quit = 0;
    SDL_Event event;

	FramerateCounter ftcounter{};

	
    while( !quit )
    {
		ftcounter.tick();
		g_time = ftcounter.getClock();

		while ( SDL_PollEvent( &event ) )
			quit |= ( event.type == SDL_QUIT );
        
        sog::gfx::runShader( &kernels, shaderCreation );

        std::string title = "Soggy!";
        title += "  FPS:" + std::to_string( 1.0 / ftcounter.getAverageDeltaTime() );
        title += "  FT:" + std::to_string( ftcounter.getAverageDeltaTime() );
        SDL_SetWindowTitle( context.pWindow, title.c_str() );

		sog::swapBuffers( &context );
	}

	sog::shutdownContext( &context );

    return 0;
}
