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

void swizzleCompletenessTestVec3()
{
	sog::vec3 v3{1,2,3};
	float v1s{};
	sog::vec2 v2s{};
	sog::vec3 v3s{};
	sog::vec4 v4s{};

	// 1 comp
	v1s = v3.x;
	v1s = v3.y;
	v1s = v3.z;
	// 2 comp
	v2s = v3.xx;
	v2s = v3.xy;
	v2s = v3.xz;
	v2s = v3.yx;
	v2s = v3.yy;
	v2s = v3.yz;
	v2s = v3.zx;
	v2s = v3.zy;
	v2s = v3.zz;
	// 3 comp
	v3s = v3.xxx;
	v3s = v3.xxy;
	v3s = v3.xxz;
	v3s = v3.xyx;
	v3s = v3.xyy;
	v3s = v3.xyz;
	v3s = v3.xzx;
	v3s = v3.xzy;
	v3s = v3.xzz;
	v3s = v3.yxx;
	v3s = v3.yxy;
	v3s = v3.yxz;
	v3s = v3.yyx;
	v3s = v3.yyy;
	v3s = v3.yyz;
	v3s = v3.yzx;
	v3s = v3.yzy;
	v3s = v3.yzz;
	v3s = v3.zxx;
	v3s = v3.zxy;
	v3s = v3.zxz;
	v3s = v3.zyx;
	v3s = v3.zyy;
	v3s = v3.zyz;
	v3s = v3.zzx;
	v3s = v3.zzy;
	v3s = v3.zzz;
	// 4 comp
	v4s = v3.xxxx;
	v4s = v3.xxxy;
	v4s = v3.xxxz;
	v4s = v3.xxyx;
	v4s = v3.xxyy;
	v4s = v3.xxyz;
	v4s = v3.xxzx;
	v4s = v3.xxzy;
	v4s = v3.xxzz;
	v4s = v3.xyxx;
	v4s = v3.xyxy;
	v4s = v3.xyxz;
	v4s = v3.xyyx;
	v4s = v3.xyyy;
	v4s = v3.xyyz;
	v4s = v3.xyzx;
	v4s = v3.xyzy;
	v4s = v3.xyzz;
	v4s = v3.xzxx;
	v4s = v3.xzxy;
	v4s = v3.xzxz;
	v4s = v3.xzyx;
	v4s = v3.xzyy;
	v4s = v3.xzyz;
	v4s = v3.xzzx;
	v4s = v3.xzzy;
	v4s = v3.xzzz;
	v4s = v3.yxxx;
	v4s = v3.yxxy;
	v4s = v3.yxxz;
	v4s = v3.yxyx;
	v4s = v3.yxyy;
	v4s = v3.yxyz;
	v4s = v3.yxzx;
	v4s = v3.yxzy;
	v4s = v3.yxzz;
	v4s = v3.yyxx;
	v4s = v3.yyxy;
	v4s = v3.yyxz;
	v4s = v3.yyyx;
	v4s = v3.yyyy;
	v4s = v3.yyyz;
	v4s = v3.yyzx;
	v4s = v3.yyzy;
	v4s = v3.yyzz;
	v4s = v3.yzxx;
	v4s = v3.yzxy;
	v4s = v3.yzxz;
	v4s = v3.yzyx;
	v4s = v3.yzyy;
	v4s = v3.yzyz;
	v4s = v3.yzzx;
	v4s = v3.yzzy;
	v4s = v3.yzzz;
	v4s = v3.zxxx;
	v4s = v3.zxxy;
	v4s = v3.zxxz;
	v4s = v3.zxyx;
	v4s = v3.zxyy;
	v4s = v3.zxyz;
	v4s = v3.zxzx;
	v4s = v3.zxzy;
	v4s = v3.zxzz;
	v4s = v3.zyxx;
	v4s = v3.zyxy;
	v4s = v3.zyxz;
	v4s = v3.zyyx;
	v4s = v3.zyyy;
	v4s = v3.zyyz;
	v4s = v3.zyzx;
	v4s = v3.zyzy;
	v4s = v3.zyzz;
	v4s = v3.zzxx;
	v4s = v3.zzxy;
	v4s = v3.zzxz;
	v4s = v3.zzyx;
	v4s = v3.zzyy;
	v4s = v3.zzyz;
	v4s = v3.zzzx;
	v4s = v3.zzzy;
	v4s = v3.zzzz;
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
