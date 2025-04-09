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

#include <math.h>

#include <thread>

#define SDL_MAIN_HANDLED
#include <SDL.h>

SogContext context;
float g_time = 0.0f;

union SogColor
{
	SogColor() = default;
	SogColor( const sog::vec4& _vec )
	{
		r = sog::clamp<float>( _vec.x, 0.0f, 1.0f ) * 255;
		g = sog::clamp<float>( _vec.y, 0.0f, 1.0f ) * 255;
		b = sog::clamp<float>( _vec.z, 0.0f, 1.0f ) * 255;
		a = sog::clamp<float>( _vec.w, 0.0f, 1.0f ) * 255;
	}

    struct
    {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };
    uint32_t dword = 255;
};

struct SogKernel
{
	uint32_t* pBase;
	uint32_t baseWidth;
	uint32_t offset;
	uint32_t size;
};

std::vector<SogKernel> sogBuildKernelList( SogContext* _pContext, uint32_t _kernelSize )
{
	uint32_t bufferSize = _pContext->width * _pContext->height;
	std::vector<SogKernel> vec{ (size_t)std::ceil( (float)bufferSize / (float)_kernelSize ) };
	
	uint32_t i = 0;
	for( uint32_t offset = 0; offset < bufferSize; offset += _kernelSize )
	{
		SogKernel& kern = vec[ i++ ];
		kern.pBase     = (uint32_t*)_pContext->pBackBuffer->pixels;
		kern.baseWidth = _pContext->width;
		kern.offset    = offset;
		kern.size      = std::min( _kernelSize, bufferSize - offset );
	}

	return vec;
}

void sogSetPixel( uint32_t _x, uint32_t _y, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
    uint32_t offset = _y * context.width + _x;
    uint32_t* pixels = (uint32_t*)context.pBackBuffer->pixels;
    pixels[ offset ] = sogMapRGBA( &context, _r, _g, _b, _a );
}

void sogSetPixel( uint32_t _offset, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
    uint32_t* pixels = (uint32_t*)context.pBackBuffer->pixels;
    pixels[ _offset ] = sogMapRGBA( &context, _r, _g, _b, _a );
}

void sogClear( uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{    
	sogBeginDraw( &context );

    uint32_t c = sogMapRGBA( &context, _r, _g, _b, _a );
    uint32_t* pixels = (uint32_t*)context.pBackBuffer->pixels;
    for( uint32_t offset = 0; offset < context.width * context.height; offset++ )
        pixels[ offset ] = c;

	sogEndDraw( &context );
}

void sogSwapBuffers() 
{
	SDL_BlitSurface( context.pBackBuffer, 0, context.pWindowSurface, 0 );
    SDL_UpdateWindowSurface( context.pWindow );
}

void sogKernelFunc( SogKernel _kernel, SogColor( *_fptr )( uint32_t, uint32_t ) )
{
	for( size_t offset = _kernel.offset; offset < _kernel.offset + _kernel.size; offset++ )
	{
		uint32_t x = offset % context.width;
		uint32_t y = offset / context.width;
		SogColor col = _fptr( x, y );
		_kernel.pBase[ offset ] = sogMapRGBA( &context, col.r, col.g, col.b, col.a );
	}
}

void sogPerPixel( std::vector<SogKernel>& _kernels, SogColor( *_fptr )( uint32_t, uint32_t ) )
{
    if( _fptr == nullptr )
        return;

	sogBeginDraw( &context );
    uint32_t* pixels = (uint32_t*)context.pBackBuffer->pixels;

	std::vector<std::thread> threads{ _kernels.size() };
	for( size_t i = 0; i < _kernels.size(); i++ )
		threads[ i ] = std::thread( sogKernelFunc, _kernels[ i ], _fptr );
	
	for( size_t i = 0; i < _kernels.size(); i++ )
		threads[ i ].join();
	
	sogEndDraw( &context );
}

SogColor perPixelFunction( uint32_t _x, uint32_t _y )
{
    SogColor fragColor{};

    float d = (float)_x / 720.0f;
    float r = cosf( d * 3.1415f + g_time ) * 0.5 + 0.5;

    fragColor.r = r * 255;
    return fragColor;
}

// https://www.shadertoy.com/view/XsXXDn
SogColor shaderCreation( uint32_t _x, uint32_t _y )
{
	sog::vec3 fragCoord{ (float)_x, (float)_y, 1.0f };
	sog::vec2 r = sog::vec2{ (float)context.width, (float)context.height };

	sog::vec3 c;
	float l, z = g_time;
	for ( int i = 0; i < 3; i++ )
	{
		sog::vec2 uv, p = fragCoord.xy / r;
		uv = p;
		p = p - 0.5f;
		p.x *= r.x / r.y;
		z += 0.07f;
		l = std::max( sog::length( p ), 0.0000001f );
		uv = uv + ( p / l * ( sin( z ) + 1.0f ) * abs( sin( l * 9.0f - z - z ) ) );
		c[ i ] = 0.01f / sog::length( sog::mod( uv, 1.0f ) - 0.5f );
	}
	
	return SogColor( sog::vec4( c / l, g_time ) );
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
	context = sogInitializeContext( 720, 480 );

    sogSwapBuffers();
    sogClear( 255, 0, 255, 255 );

	//auto kernels = sogBuildKernelList( &context, 720, 480 / 8 );
	auto kernels = sogBuildKernelList( &context, 150 * 150 );

    int quit = 0;
    SDL_Event event;

	std::chrono::high_resolution_clock timer;
	std::chrono::steady_clock::time_point start = timer.now();

	FramerateCounter ftcounter{};

    while( !quit )
    {
		ftcounter.tick();
		g_time = ftcounter.getClock();

		while ( SDL_PollEvent( &event ) )
			quit |= ( event.type == SDL_QUIT );
        
        sogPerPixel( kernels, shaderCreation );

        std::string title = "Soggy!";
        title += "  FPS:" + std::to_string( 1.0 / ftcounter.getAverageDeltaTime() );
        title += "  FT:" + std::to_string( ftcounter.getAverageDeltaTime() );
        SDL_SetWindowTitle( context.pWindow, title.c_str() );

		sogSwapBuffers();
	}

	sogShutdownContext( &context );

    return 0;
}
