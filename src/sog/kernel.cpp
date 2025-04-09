#include "kernel.h"

#include <sog/context.h>
#include <sog/math.h>

#include <SDL.h>

sog::KernelList sog::buildKernelList( sog::Context* _pContext, uint32_t _kernelSize )
{
	uint32_t bufferSize = _pContext->width * _pContext->height;
	KernelList list{
		_pContext,
		std::vector<Kernel>{ (size_t)std::ceil( (float)bufferSize / (float)_kernelSize ) }
	};

	uint32_t i = 0;
	for( uint32_t offset = 0; offset < bufferSize; offset += _kernelSize )
	{
		sog::Kernel& kern = list.kernels[ i++ ];
		kern.pBase = (uint32_t*)_pContext->pBackBuffer->pixels;
		kern.baseWidth = _pContext->width;
		kern.offset = offset;
		kern.size = std::min( _kernelSize, bufferSize - offset );
	}

	return list;
}