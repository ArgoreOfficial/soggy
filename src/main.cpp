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

#include <math.h>

#include <thread>

#define SDL_MAIN_HANDLED
#include <SDL.h>

sog::Context context;
float g_time = 0.0f;
sog::vec2f iResolution{};

// https://www.shadertoy.com/view/XsXXDn
void shaderCreation( sog::vec4f& _outFragColor, sog::vec2f _fragCoord )
{
	sog::vec2f r = sog::vec2f{ (float)context.width, (float)context.height };

	sog::vec3f c;
	float l, z = g_time;
	for ( int i = 0; i < 3; i++ )
	{
		sog::vec2f uv, p = _fragCoord / r;
		uv = p;
		p = p - 0.5f;
		p.x *= r.x / r.y;
		z += 0.07f;
		l = std::max( sog::length( p ), 0.0000001f );
		uv = uv + ( p / l * ( sin( z ) + 1.0f ) * abs( sin( l * 9.0f - z - z ) ) );
		c[ i ] = 0.01f / sog::length( sog::mod( uv, 1.0f ) - 0.5f );
	}
	
	_outFragColor = sog::vec4f( c / l, g_time );
}

#define iterations 7
#define volsteps 7
#define pi 3.141592653589793

// https://www.shadertoy.com/view/WcfXRs
void shaderMilky( sog::vec4f& fragColor, sog::vec2f fragCoord )
{
	//Initialize animate time (10x speed)
	float t = g_time / 0.1,
	//Fractional starting index
	f = sog::fract( -t ),
	//Whole-index for star
	w = 0.0;

		//Screen uvs, centered and aspect correct (-0.5 to +0.5)
	sog::vec2f suv = ( fragCoord - iResolution * 0.5 ) / iResolution.y;

	//Prepare the sum of the star colors
	sog::vec3f rgb{ 0.0f };

	//Loop through 100 stars
	for( float i = f; i < 1e2; i++ )
	{
		//Find the whole-number star index
		w = std::round( i + t );
		//Square to prevent linear patterns. sin is a better alternative
		w *= w; //sin(w)
		//Pick a color using the index
		rgb += ( sog::cos( w + sog::vec3f( 0, 1, 2 ) ) + 1. )
		//Vary the brightness with the index
		* std::exp( sog::cos( w / .1 ) / .6 )
		//Fade in and out
		* std::min( 1e3f - i / .1f + 9.f, i ) / 5e4
		//Attentuate outward
		/ sog::length( suv
		//Set the star position
		+ .05f * sog::cos( w / .31f + sog::vec2f( 0.f, 5.f ) ) * sqrt( i ) );
	}

	//Increase contrast
	rgb *= rgb;

	//Tanh tonemap:
	//https://www.shadertoy.com/view/ms3BD7
	rgb = tanh( rgb );

	fragColor = sog::vec4f( rgb, 1.0 );
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

int main( int argc, char* argv[] )
{
	context = sog::initializeContext( 720, 480 );
	iResolution = { (float)context.width, (float)context.height };

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
