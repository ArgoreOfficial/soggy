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

struct vec2i
{
	vec2i() = default;
	vec2i( int32_t p_x, int32_t p_y ) : 
		x{ p_x }, 
		y{ p_y } 
	{};

	vec2i( const sog::vec2& p_vec2 ) : 
		x{ (int32_t)p_vec2.x }, 
		y{ (int32_t)p_vec2.y } 
	{};
	
	int32_t x, y;
};

int32_t determinant( vec2i p_a, vec2i p_b, vec2i p_c )
{
	return ( p_b.x - p_a.x ) * ( p_c.y - p_a.y ) - 
		   ( p_b.y - p_a.y ) * ( p_c.x - p_a.x );
}

void sog::gfx::raster_triangle( uint32_t* p_pixels, uint32_t p_buffer_width, uint32_t p_buffer_height, sog::vec2 v0, sog::vec2 v1, sog::vec2 v2 ) {
	const int32_t min_x = sog::clamp<int32_t>( sog::min( v0.x, v1.x, v2.x ), 0, p_buffer_width );
	const int32_t max_x = sog::clamp<int32_t>( sog::max( v0.x, v1.x, v2.x ), 0, p_buffer_width );
	const int32_t min_y = sog::clamp<int32_t>( sog::min( v0.y, v1.y, v2.y ), 0, p_buffer_height );
	const int32_t max_y = sog::clamp<int32_t>( sog::max( v0.y, v1.y, v2.y ), 0, p_buffer_height );

	const int32_t A01 = v0.y - v1.y; const int32_t B01 = v1.x - v0.x;
	const int32_t A12 = v1.y - v2.y; const int32_t B12 = v2.x - v1.x;
	const int32_t A20 = v2.y - v0.y; const int32_t B20 = v0.x - v2.x;

	// Barycentric coordinates at minX/minY corner
	vec2i p = vec2i{ min_x, min_y };
	int32_t w0_row = determinant( v1, v2, p );
	int32_t w1_row = determinant( v2, v0, p );
	int32_t w2_row = determinant( v0, v1, p );
	
	uint32_t red = sog::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }.bgra8;

	// Rasterize
	for ( p.y = min_y; p.y <= max_y; p.y++ )
	{
		// Barycentric coordinates at start of row
		int32_t w0 = w0_row;
		int32_t w1 = w1_row;
		int32_t w2 = w2_row;

		for ( p.x = min_x; p.x <= max_x; p.x++ )
		{
			// If p is on or inside all edges, render pixel.
			if ( ( w0 | w1 | w2 ) >= 0 )
			{
				uint32_t buffer_offset = p.y * p_buffer_width + p.x;
				uint32_t total = w0 + w1 + w2;

				const float b0 = (float)w0 / (float)total;
				const float b1 = (float)w1 / (float)total;
				const float b2 = (float)w2 / (float)total;

				p_pixels[ buffer_offset ] = sog::vec4( b0, b1, b2, 1.0f ).bgra8;
			}

			// One step to the right
			w0 += A12;
			w1 += A20;
			w2 += A01;
		}

		// One row step
		w0_row += B12;
		w1_row += B20;
		w2_row += B01;
	}
}



