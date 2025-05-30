#ifndef SOG_GRAPHICS_H
#define SOG_GRAPHICS_H

#include <sog/math.h>

#include <stdint.h>

namespace sog {

union color
{
	color() = default;

	color( const sog::vec4& _vec )
	{
		rgba.r = sog::clamp<float>( _vec.x(), 0.0f, 1.0f ) * 255;
		rgba.g = sog::clamp<float>( _vec.y(), 0.0f, 1.0f ) * 255;
		rgba.b = sog::clamp<float>( _vec.z(), 0.0f, 1.0f ) * 255;
		rgba.a = sog::clamp<float>( _vec.w(), 0.0f, 1.0f ) * 255;
	}

	color( uint32_t p_ui32 ) {
		rgba.dword = p_ui32;
	}

	color( uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a ) {
		rgba.r = p_r;
		rgba.b = p_b;
		rgba.g = p_g;
		rgba.a = p_a;
	}


	struct
	{
		struct
		{
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};
		uint32_t dword;
	} rgba;

	union
	{
		struct
		{
			uint8_t b;
			uint8_t g;
			uint8_t r;
			uint8_t a;
		};
		uint32_t dword;
	} bgra;
};


struct Context;
struct KernelList;

namespace gfx {

typedef void( *shader_main_t )( sog::vec4& p_out, sog::vec2 p_in );
typedef int( *raster_shader_t )( sog::vec4& p_out, int32_t p_bary0, int32_t p_bary1, int32_t p_bary2 );

void clear( Context* p_context, uint32_t p_rgba8 );

void runShader( KernelList* p_kernel_list, shader_main_t p_shader );

void line( uint32_t* p_pixels, const uint16_t p_buffer_width, const uint16_t p_buffer_height, int16_t p_x0, int16_t p_y0, int16_t p_x1, int16_t p_y1 );
void raster_triangle( raster_shader_t p_shader, uint32_t* p_pixels, uint32_t p_buffer_width, uint32_t p_buffer_height, sog::vec2 v0, sog::vec2 v1, sog::vec2 v2 );

}

}

#endif
