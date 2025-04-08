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
#include <math.h>

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

typedef float decimal_type_t;

#define VEC2_OPERATOR(_op) \
vec2 operator##_op##( const vec2& _lhs, const decimal_type_t& _rhs ) { \
	return vec2{ _lhs.x _op _rhs, _lhs.y _op _rhs }; \
} \
vec2 operator##_op##( const decimal_type_t& _lhs, const vec2& _rhs ) { \
	return vec2{ _lhs _op _rhs.x, _lhs _op _rhs.y }; \
} \
vec2 operator##_op##( const vec2& _lhs, const vec2& _rhs ) { \
	return vec2{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y }; \
}

#define VEC3_OPERATOR(_op) \
vec3 operator##_op##( const vec3& _lhs, const decimal_type_t& _rhs ) { \
	return vec3{ _lhs.x _op _rhs, _lhs.y _op _rhs, _lhs.z _op _rhs }; \
} \
vec3 operator##_op##( const decimal_type_t& _lhs, const vec3& _rhs ) { \
	return vec3{ _lhs _op _rhs.x, _lhs _op _rhs.y, _lhs _op _rhs.z }; \
} \
vec3 operator##_op##( const vec3& _lhs, const vec3& _rhs ) { \
	return vec3{ _lhs.x _op _rhs.x, _lhs.y _op _rhs.y, _lhs.z _op _rhs.z }; \
}

struct vec2
{
	decimal_type_t x, y;


};

VEC2_OPERATOR( / );
VEC2_OPERATOR( * );
VEC2_OPERATOR( + );
VEC2_OPERATOR( - );

struct vec3
{
	decimal_type_t x, y, z;

	vec2 xy() {
		return { x, y };
	}

	decimal_type_t& operator []( size_t _index ) {
		return ( &x )[ _index ];
	}
};

VEC3_OPERATOR( / );
VEC3_OPERATOR( * );
VEC3_OPERATOR( +);
VEC3_OPERATOR( -);

template<typename Ty>
Ty clamp( const Ty& _v, const Ty& _min, const Ty& _max )
{
	return std::max( std::min<Ty>( _v, _max ), _min );
}

struct vec4
{
	decimal_type_t x, y, z, w;
	vec4() = default;
	vec4( const vec3& _vec, decimal_type_t _w ) : 
		x{ _vec.x }, y{ _vec.y }, z{ _vec.z }, w{ _w } 
	{ }

	operator SogColor() {
		SogColor c;
		c.r = clamp<float>( x, 0.0f, 1.0f ) * 255;
		c.g = clamp<float>( y, 0.0f, 1.0f ) * 255;
		c.b = clamp<float>( z, 0.0f, 1.0f ) * 255;
		c.a = clamp<float>( w, 0.0f, 1.0f ) * 255;
		return c;
	}
};

decimal_type_t length( const vec2& _vec2 ) {
	return std::sqrt( _vec2.x * _vec2.x + _vec2.y * _vec2.y );
}

vec2 floor( const vec2& _t ) {
	return vec2{
		floor( _t.x ),
		floor( _t.y )
	};
}

vec2 mod( const vec2& _x, decimal_type_t _y ) {
	return _x - _y * floor( _x / _y );
}

// https://www.shadertoy.com/view/XsXXDn
SogColor shaderCreation( uint32_t _x, uint32_t _y )
{
	vec3 fragCoord{ (float)_x, (float)_y, 1.0f };
	vec2 r = vec2{ (float)context.width, (float)context.height };

	vec3 c{};
	float l, z = g_time;
	for ( int i = 0; i < 3; i++ )
	{
		vec2 uv, p = fragCoord.xy() / r;
		uv = p;
		p = p - 0.5f;
		p.x *= r.x / r.y;
		z += 0.07f;
		l = length( p );
		uv = uv + ( p / l * ( sin( z ) + 1.0f ) * abs( sin( l * 9.0f - z - z ) ) );
		c[ i ] = 0.01f / length( mod( uv, 1.0f ) - 0.5f );
	}
	
	SogColor fragColor = vec4( c / l, g_time );
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
        
        sogPerPixel( shaderCreation );

        std::string title = "Soggy!    FPS: ";
        title += std::to_string( 1 );
        SDL_SetWindowTitle( context.pWindow, title.c_str() );

		sogSwapBuffers();
	}

	sogShutdownContext( &context );

    return 0;
}
