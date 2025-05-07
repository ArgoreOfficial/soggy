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
		p.x() *= r.x() / r.y();
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

	sog::vec2 uv = lerp( UVs[ 0 ], UVs[ 1 ], bary.y() );
	uv = lerp( uv, UVs[ 2 ], bary.z() );

	p_out = sog::vec4( uv.x(), uv.y(), 0, 1 );
	return 1;
}

int main( int argc, char* argv[] )
{
	context = sog::initializeContext( 720, 480 );
	iResolution = { (float)context.width, (float)context.height };

    sog::swapBuffers( &context );
    
	const uint32_t size = (720 * 480) / ( std::thread::hardware_concurrency() - 1 );
	sog::KernelList kernels = sog::buildKernelList( &context, size );

    int quit = 0;
    SDL_Event event;

	sog::vec2 test1{ 5.0f, 2.0f };
	
	sog::vec3 test2{ 3,4,3 }; // 3 1 3 
	test2.xz = test2.yy;      // 4 4 4
	test2.x() = 3;            // 3 4 4
	// test2.xz *= 2;

	sog::vec3 test3{};
	test3 = test1.xxx;

	FramerateCounter ftcounter{};

    while( !quit )
    {
		ftcounter.tick();
		g_time = ftcounter.getClock();

		while ( SDL_PollEvent( &event ) )
			quit |= ( event.type == SDL_QUIT );
		
		sog::gfx::clear( &context, sog::vec4(0,0,0,1).bgra8() );

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
