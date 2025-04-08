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

#include <immintrin.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

SDL_Window* g_pWindow;
SDL_Surface* g_pWindowSurface;

SDL_Rect onepix_rect;
SDL_Texture* onepix_texture;
SDL_Renderer* surface_renderer;

uint32_t g_currentFrame = 0;

uint32_t g_width, g_height;

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

void sogInitialize( uint32_t _width, uint32_t _height )
{
    g_width  = _width;
    g_height = _height;

    SDL_Init( SDL_INIT_EVERYTHING );

    g_pWindow = SDL_CreateWindow( "Soggy!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0 );
    surface_renderer = SDL_CreateRenderer( g_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    g_pWindowSurface = SDL_GetWindowSurface( g_pWindow );
    onepix_texture = SDL_CreateTexture( surface_renderer, g_pWindowSurface->format->format, SDL_TEXTUREACCESS_STREAMING, 1, 1 );

    onepix_rect.h = 1;
    onepix_rect.w = 1;
    onepix_rect.x = 0;
    onepix_rect.y = 0;
}

void sogQuit()
{
    SDL_Quit();
}

void sogSetPixel( SDL_Surface* _pSurface, uint32_t _x, uint32_t _y, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
    uint32_t offset = _y * g_width + _x;
    uint32_t* pixels = (uint32_t*)_pSurface->pixels;
    pixels[ offset ] = SDL_MapRGBA( _pSurface->format, _r, _g, _b, _a );
}

void sogSetPixel( SDL_Surface* _pSurface, uint32_t _offset, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
    uint32_t* pixels = (uint32_t*)_pSurface->pixels;
    pixels[ _offset ] = SDL_MapRGBA( _pSurface->format, _r, _g, _b, _a );
}

void sogClear( SDL_Surface* _pSurface, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{    
    SDL_LockSurface( _pSurface );

    uint32_t c = SDL_MapRGBA( _pSurface->format, _r, _g, _b, _a );
    uint32_t* pixels = (uint32_t*)_pSurface->pixels;
    for( uint32_t offset = 0; offset < g_width * g_height; offset++ )
        pixels[ offset ] = c;

    SDL_UnlockSurface( _pSurface );
}

void sogSwapBuffers() 
{
    //SDL_BlitSurface( g_pCurrentSurface, 0, g_pWindowSurface, 0 );
    
    SDL_RenderCopy( surface_renderer, onepix_texture, NULL, &onepix_rect );
    SDL_RenderPresent( surface_renderer );
    SDL_UpdateWindowSurface( g_pWindow );
    
    g_currentFrame++;
}

void sogPerPixel( SDL_Surface* _pSurface, SogColor( *_fptr )( uint32_t, uint32_t ) )
{
    if( _fptr == nullptr )
        return;

    SDL_LockSurface( _pSurface );
    uint32_t* pixels = (uint32_t*)_pSurface->pixels;
    for( uint32_t y = 0; y < g_height; y++ )
    {
        for( uint32_t x = 0; x < g_width; x++ )
        {
            SogColor col = _fptr( x, y );
            uint32_t offset = y * g_width + x;
            pixels[ offset ] = SDL_MapRGBA( _pSurface->format, col.r, col.g, col.b, col.a );
        }
    }
    SDL_UnlockSurface( _pSurface );
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
    sogClear( g_pWindowSurface, 255, 0, 255, 255 );

    /*
    {
        auto src_buffer = static_cast<uint32_t*>( g_pSwapChain[ ( g_currentFrame + 1 )     % 2 ]->pixels );
        auto dst_buffer = static_cast<uint32_t*>( g_pSwapChain[ ( g_currentFrame ) % 2 ]->pixels );
        auto src_surface = g_pSwapChain[ ( g_currentFrame + 1 )     % 2 ];
        auto dst_surface = g_pSwapChain[ ( g_currentFrame ) % 2 ];
        SDL_LockSurface( src_surface );
        SDL_LockSurface( dst_surface );

        SogColor c[ 8 ] = {
            {255,255,255,255},
            {255,255,255,255},
            {255,255,255,255},
            {255,255,255,255},
            {255,255,255,255},
            {255,255,255,255},
            {255,255,255,255},
            {255,255,255,255},
        };

        __m256i a;
        __m256i b = _mm256_load_si256( ( __m256i* )c );
        for( uint32_t offset = 0; offset < g_width * g_height; offset += 8 )
        {
            __m256i* src = ( __m256i* )( &src_buffer[ offset ] );
            __m256i* dst = ( __m256i* )( &dst_buffer[ offset ] );
            a = _mm256_load_si256( src );
            _mm256_store_si256( dst, _mm256_subs_epi8( b, a ) );
        }

        for( size_t i = 0; i < g_width * g_height; i++ )
        {
            SogColor* c = (SogColor*)( &dst_buffer[ i ] );
            c->a = 255;
        }

        SDL_UnlockSurface( dst_surface );
        SDL_UnlockSurface( src_surface );
    }
    */


    int quit = 0;
    SDL_Event event;
    
    while( !quit )
    {
        
        double deltatime = 1.0 / 60.0; //  static_cast<double>( elapsed.count() ) / 1000;
        g_time += deltatime;

        sogSwapBuffers();

        while( SDL_PollEvent( &event ) )
            if( event.type == SDL_QUIT )
                quit = 1;
        
        sogPerPixel( g_pWindowSurface, perPixelFunction );

        std::string title = "Soggy!    FPS: ";
        title += std::to_string( 1 );
        SDL_SetWindowTitle( g_pWindow, title.c_str() );

        
        // SDL_Delay( 10 );
    }

    sogQuit();

    return 0;
}
