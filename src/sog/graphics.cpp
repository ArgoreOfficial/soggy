#include "graphics.h"

#include <sog/context.h>
#include <sog/kernel.h>
#include <sog/math.h>

#include <thread>

#include <SDL.h>

void sog::gfx::clear( Context* p_context, uint32_t p_rgba8 )
{
	sog::beginDraw( p_context );

	uint32_t* pixels = (uint32_t*)p_context->pBackBuffer->pixels;
	for( uint32_t offset = 0; offset < p_context->width * p_context->height; offset++ )
		pixels[ offset ] = p_rgba8;

	sog::endDraw( p_context );
}

void sogKernelFunc( sog::Context* p_context, sog::Kernel p_kernel, sog::gfx::shader_main_t p_shader )
{
	sog::vec4 v4col;
	
	for( size_t offset = p_kernel.offset; offset < p_kernel.offset + p_kernel.size; offset++ )
	{
		uint32_t x = offset % p_kernel.baseWidth;
		uint32_t y = offset / p_kernel.baseWidth;

		p_shader( v4col, sog::vec2{ (float)x, (float)y } );
		p_kernel.pBase[ offset ] = v4col.rgba8;
	}
}

void sog::gfx::runShader( KernelList* p_kernel_list, shader_main_t p_shader )
{
	if( p_shader == nullptr )
		return;

	sog::beginDraw( p_kernel_list->pContext );
	uint32_t* pixels = (uint32_t*)p_kernel_list->pContext->pBackBuffer->pixels;

	std::vector<std::thread> threads{ p_kernel_list->kernels.size() };
	for( size_t i = 0; i < p_kernel_list->kernels.size(); i++ )
		threads[ i ] = std::thread( sogKernelFunc, p_kernel_list->pContext, p_kernel_list->kernels[ i ], p_shader );

	for( size_t i = 0; i < p_kernel_list->kernels.size(); i++ )
		threads[ i ].join();

	sog::endDraw( p_kernel_list->pContext );
}

void sog::gfx::line( uint32_t* p_pixels, const uint16_t p_buffer_width, const uint16_t p_buffer_height, int16_t p_x0, int16_t p_y0, int16_t p_x1, int16_t p_y1 )
{
	int16_t dx = abs( p_x1 - p_x0 );
	int16_t sx = p_x0 < p_x1 ? 1 : -1;
	int16_t dy = -abs( p_y1 - p_y0 );
	int16_t sy = p_y0 < p_y1 ? 1 : -1;
	int16_t error = dx + dy;
	uint32_t buffer_offset;

	uint32_t red   = sog::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }.bgra8; 
	uint32_t green = sog::vec4{ 0.0f, 1.0f, 0.0f, 1.0f }.bgra8;

	while ( true )
	{
		bool draw = false;
		if ( p_x0 >= 0 && p_x0 < p_buffer_width && p_y0 >= 0 && p_y0 < p_buffer_height )
		{
			draw = true;
			buffer_offset = p_y0 * p_buffer_width + p_x0;
		}

		int16_t e2 = 2 * error;

		if ( e2 >= dy )
		{
			if( draw )
				p_pixels[ buffer_offset ] = red;

			if ( p_x0 == p_x1 )
				break;

			error = error + dy;
			p_x0 = p_x0 + sx;
		}

		if ( e2 <= dx )
		{
			if ( draw )
				p_pixels[ buffer_offset ] = green;

			if ( p_y0 == p_y1 )
				break;

			error = error + dx;
			p_y0 = p_y0 + sy;
		}
	}
}


int32_t determinant( sog::vec2i p_a, sog::vec2i p_b, sog::vec2i p_c )
{
	return ( p_b.x - p_a.x ) * ( p_c.y - p_a.y ) - 
		   ( p_b.y - p_a.y ) * ( p_c.x - p_a.x );
}

uint32_t pack_rgba8( uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a ) {
	uint32_t v = p_r; 
	v |= p_g << 8; 
	v |= p_b << 16; 
	v |= p_a << 24;
	return v;
}

uint32_t pack_bgra8( uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a ) {
	return pack_rgba8( p_b, p_g, p_r, p_a );
}

void sog::gfx::raster_triangle( uint32_t* p_pixels, uint32_t p_buffer_width, uint32_t p_buffer_height, sog::vec2 v0, sog::vec2 v1, sog::vec2 v2 ) {
	if ( !p_pixels )
		return;
	
	const int32_t min_x = sog::clamp<int32_t>( sog::min( v0.x, v1.x, v2.x ), 0, p_buffer_width );
	const int32_t max_x = sog::clamp<int32_t>( sog::max( v0.x, v1.x, v2.x ), 0, p_buffer_width );
	const int32_t min_y = sog::clamp<int32_t>( sog::min( v0.y, v1.y, v2.y ), 0, p_buffer_height );
	const int32_t max_y = sog::clamp<int32_t>( sog::max( v0.y, v1.y, v2.y ), 0, p_buffer_height );

	const int32_t A01 = v0.y - v1.y; const int32_t B01 = v1.x - v0.x;
	const int32_t A12 = v1.y - v2.y; const int32_t B12 = v2.x - v1.x;
	const int32_t A20 = v2.y - v0.y; const int32_t B20 = v0.x - v2.x;

	vec2i p = vec2i{ min_x, min_y };
	int32_t bary0_row = determinant( v1, v2, p );
	int32_t bary1_row = determinant( v2, v0, p );
	int32_t bary2_row = determinant( v0, v1, p );
	
	for ( p.y = min_y; p.y <= max_y; p.y++ )
	{
		int32_t bary0_col = bary0_row;
		int32_t bary1_col = bary1_row;
		int32_t bary2_col = bary2_row;

		for ( p.x = min_x; p.x <= max_x; p.x++ )
		{
			if ( ( bary0_col | bary1_col | bary2_col ) >= 0 )
			{
				uint32_t buffer_offset = p.y * p_buffer_width + p.x;
				int32_t total = bary0_col + bary1_col + bary2_col;

				// float real_bary0 = (float)bary0 / (float)total;

				p_pixels[ buffer_offset ] = pack_bgra8( (bary0_col*255) / total, (bary1_col*255) / total, (bary2_col*255) / total, 255 );
			}

			bary0_col += A12;
			bary1_col += A20;
			bary2_col += A01;
		}

		// One row step
		bary0_row += B12;
		bary1_row += B20;
		bary2_row += B01;
	}
}



