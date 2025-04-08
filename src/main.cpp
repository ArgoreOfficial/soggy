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

#include <context.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

SogContext context;
float g_time = 0.0f;

union SogColor
{
    struct
    {
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
    };
    uint32_t dword = 255;
};

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

void sogPerPixel( SogColor( *_fptr )( uint32_t, uint32_t ) )
{
    if( _fptr == nullptr )
        return;

	sogBeginDraw( &context );
    uint32_t* pixels = (uint32_t*)context.pBackBuffer->pixels;
    for( uint32_t y = 0; y < context.height; y++ )
    {
        for( uint32_t x = 0; x < context.width; x++ )
        {
            SogColor col = _fptr( x, y );
            uint32_t offset = y * context.width + x;
            pixels[ offset ] = sogMapRGBA( &context, col.r, col.g, col.b, col.a );
        }
    }
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

int main( int argc, char* argv[] )
{
	context = sogInitializeContext( 720, 480 );

    sogSwapBuffers();
    sogClear( 255, 0, 255, 255 );

    int quit = 0;
    SDL_Event event;

    while( !quit )
    {
        
        double deltatime = 1.0 / 60.0; //  static_cast<double>( elapsed.count() ) / 1000;
        g_time += deltatime;

		while ( SDL_PollEvent( &event ) )
			quit |= ( event.type == SDL_QUIT );
        
        sogPerPixel( perPixelFunction );

        std::string title = "Soggy!    FPS: ";
        title += std::to_string( 1 );
        SDL_SetWindowTitle( context.pWindow, title.c_str() );

		sogSwapBuffers();
	}

	sogShutdownContext( &context );

    return 0;
}
