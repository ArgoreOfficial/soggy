#include "graphics.h"

#include <sog/context.h>
#include <sog/kernel.h>

#include <thread>

#include <SDL.h>

void sog::gfx::clear( Context* _pContext, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
	sog::beginDraw( _pContext );

	uint32_t c = sog::mapRGBA( _pContext, _r, _g, _b, _a );
	uint32_t* pixels = (uint32_t*)_pContext->pBackBuffer->pixels;
	for( uint32_t offset = 0; offset < _pContext->width * _pContext->height; offset++ )
		pixels[ offset ] = c;

	sog::endDraw( _pContext );
}

void sogKernelFunc( sog::Context* _pContext, sog::Kernel _kernel, sog::gfx::shader_main_t _shader )
{
	sog::vec4f v4col;
	
	for( size_t offset = _kernel.offset; offset < _kernel.offset + _kernel.size; offset++ )
	{
		uint32_t x = offset % _kernel.baseWidth;
		uint32_t y = offset / _kernel.baseWidth;

		_shader( v4col, sog::vec2f{ (float)x, (float)y } );
		sog::color col = v4col; // convert to rgba8

		_kernel.pBase[ offset ] = sog::mapRGBA( _pContext, col.r, col.g, col.b, col.a );
	}
}

void sog::gfx::runShader( KernelList* _kernelList, shader_main_t _shader )
{
	if( _shader == nullptr )
		return;

	sog::beginDraw( _kernelList->pContext );
	uint32_t* pixels = (uint32_t*)_kernelList->pContext->pBackBuffer->pixels;

	std::vector<std::thread> threads{ _kernelList->kernels.size() };
	for( size_t i = 0; i < _kernelList->kernels.size(); i++ )
		threads[ i ] = std::thread( sogKernelFunc, _kernelList->pContext, _kernelList->kernels[ i ], _shader );

	for( size_t i = 0; i < _kernelList->kernels.size(); i++ )
		threads[ i ].join();

	sog::endDraw( _kernelList->pContext );
}




