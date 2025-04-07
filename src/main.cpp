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

#define SDL_MAIN_HANDLED
#include <SDL.h>

SDL_Window* g_pWindow;

SDL_Surface* g_pWindowSurface;
SDL_Surface* g_pSwapChain[ 2 ];
SDL_Surface* g_pCurrentSurface;
uint32_t g_currentFrame = 0;

uint32_t g_width, g_height;
uint32_t* g_pScreenBuffer;

float g_time = 0.0f;

struct SogColor
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

void sogInitialize( uint32_t _width, uint32_t _height )
{
    g_width  = _width;
    g_height = _height;

    SDL_Init( SDL_INIT_EVERYTHING );

    g_pWindow = SDL_CreateWindow( "Soggy!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0 );
    g_pWindowSurface = SDL_GetWindowSurface( g_pWindow );

    uint32_t format = SDL_PIXELFORMAT_RGBA8888;

    g_pSwapChain[ 0 ] = SDL_CreateRGBSurfaceWithFormat( 0, _width, _height, 0, format );
    g_pSwapChain[ 1 ] = SDL_CreateRGBSurfaceWithFormat( 0, _width, _height, 0, format );

    g_pCurrentSurface = g_pSwapChain[ g_currentFrame % 2 ];
}

void sogQuit()
{
    SDL_Quit();
}

void sogSetPixel( uint32_t _x, uint32_t _y, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
    uint32_t offset = _y * g_width + _x;
    g_pScreenBuffer[ offset ] = SDL_MapRGBA( g_pCurrentSurface->format, _r, _g, _b, _a );
}

void sogSetPixel( uint32_t _offset, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
    g_pScreenBuffer[ _offset ] = SDL_MapRGBA( g_pCurrentSurface->format, _r, _g, _b, _a );
}

void sogClear( uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a ) 
{
    SDL_LockSurface( g_pCurrentSurface );
    for( uint32_t offset = 0; offset < g_width * g_height; offset++ )
        sogSetPixel( offset, _r, _g, _b, _a );
    SDL_UnlockSurface( g_pCurrentSurface );
}

void sogSwapBuffers() 
{
    g_pScreenBuffer = static_cast<uint32_t*>( g_pSwapChain[ g_currentFrame % 2 ]->pixels );
    g_pCurrentSurface = g_pSwapChain[ g_currentFrame % 2 ];

    SDL_BlitSurface( g_pCurrentSurface, 0, g_pWindowSurface, 0 );
    SDL_UpdateWindowSurface( g_pWindow );

    g_currentFrame++;
}

void sogPerPixel( SogColor( *_fptr )( uint32_t, uint32_t ) )
{
    if( _fptr == nullptr )
        return;

    SDL_LockSurface( g_pCurrentSurface );
    for( uint32_t y = 0; y < g_height; y++ )
    {
        for( uint32_t x = 0; x < g_width; x++ )
        {
            SogColor col = _fptr( x, y );
            uint32_t offset = y * g_width + x;
            g_pScreenBuffer[ offset ] = SDL_MapRGBA( g_pCurrentSurface->format, col.r, col.g, col.b, col.a );
        }
    }
    SDL_UnlockSurface( g_pCurrentSurface );
}

SogColor perPixelFunction( uint32_t _x, uint32_t _y )
{
    SogColor fragColor{};

    float d = (float)_x / (float)g_width;
    float r = cosf( d * 3.1415f + g_time ) * 0.5 + 0.5;

    fragColor.r = r * 255;
    return fragColor;
}

int main( int argc, char* argv[] )
{
    sogInitialize( 720, 480 );

    sogSwapBuffers();
    sogClear( 255, 0, 255, 255 );
    
    sogSwapBuffers();
    sogClear( 0, 255, 255, 255 );

    int quit = 0;
    SDL_Event event;
    
    auto start = std::chrono::system_clock::now();

    while( !quit )
    {
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( end - start );
        double deltatime = static_cast<double>( elapsed.count() ) / 1000;
        start = end;

        g_time += deltatime;

        while( SDL_PollEvent( &event ) )
            if( event.type == SDL_QUIT )
                quit = 1;
        
        sogPerPixel( perPixelFunction );

        sogSwapBuffers();

        SDL_Delay( 10 );
    }

    sogQuit();

    return 0;
}
