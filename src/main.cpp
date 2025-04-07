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
#include <Windows.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

SDL_Window* g_pWindow;

SDL_Surface* g_pWindowSurface;
SDL_Surface* g_pSwapChain[ 2 ];
SDL_Surface* g_pCurrentSurface;
uint32_t g_currentFrame = 0;

uint32_t g_width, g_height;
uint32_t* g_pScreenBuffer;

HDC g_hdcMem;

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

            SetPixel( g_hdcMem, x, y, 0x000000FF );
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



    // WINDOWS
    // Define and initialize variables
    HDC          hdc;
    HBITMAP      hbmMem;
    HANDLE       hOld;
    RECT rect;
    SIZE sz;
    int font_size = 20;
    int location_x = 40;
    int location_y = 40;
    int border = font_size / 4;
    int duration = 10000;           // In miliseconds. The notification will always stay up more time
    wchar_t* font_face = (wchar_t*)L"Consolas";
    wchar_t* message = (wchar_t*)L"Bobber Kurwa";

    // Acquire screen
    hdc = ::GetDC( 0 );

    // Create an off-screen DC for double-buffering
    g_hdcMem = CreateCompatibleDC( hdc );
    hbmMem = CreateCompatibleBitmap( hdc, g_width + 2 * border, g_height + 2 * border );

    // Configure off-screen DC
    SetBkMode( g_hdcMem, OPAQUE );
    SetTextColor( g_hdcMem, RGB( 125, 125, 255 ) );
    SetBkColor( g_hdcMem, RGB( 0, 0, 0 ) );
    hOld = SelectObject( g_hdcMem, hbmMem );
    


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

        // Transfer the off-screen DC to the screen
        BitBlt( hdc, location_x, location_y, g_width + 2 * border, g_height + 2 * border, g_hdcMem, -5, -5, SRCCOPY );

        // Don't eat all the cpu!
        //SDL_Delay( 10 );
    }






    // Delete notification right after time expires
    ::InvalidateRect( 0, &rect, false );
    ::UpdateWindow( 0 );

    // Free-up the off-screen DC
    SelectObject( g_hdcMem, hOld );
    DeleteObject( hbmMem );
    DeleteDC( g_hdcMem );

    // Release created objects
    
    ::ReleaseDC( 0, hdc );

    sogQuit();

    return 0;
}
