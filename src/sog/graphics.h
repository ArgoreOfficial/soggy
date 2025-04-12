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


struct Context;
struct KernelList;

namespace gfx {

typedef void( *shader_main_t )( sog::vec4& p_out, sog::vec2 p_in );

void clear( Context* p_context, uint32_t p_rgba8 );

void runShader( KernelList* p_kernel_list, shader_main_t p_shader );

void line( uint32_t* p_pixels, const uint16_t p_buffer_width, const uint16_t p_buffer_height, int16_t p_x0, int16_t p_y0, int16_t p_x1, int16_t p_y1 );
void raster_triangle( uint32_t* p_pixels, uint32_t p_buffer_width, uint32_t p_buffer_height, sog::vec2 v0, sog::vec2 v1, sog::vec2 v2 );

}

}

#endif
