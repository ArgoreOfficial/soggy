#ifndef SOG_KERNEL_H
#define SOG_KERNEL_H

#include <vector>

namespace sog {

struct Context;

struct Kernel
{
	uint32_t* pBase;
	uint32_t baseWidth;
	uint32_t offset;
	uint32_t size;
};

struct KernelList
{
	Context* pContext = nullptr;
	std::vector<Kernel> kernels;
};

KernelList buildKernelList( sog::Context* _pContext, uint32_t _kernelSize );

}

#endif
