#ifndef SOG_GRAPHICS_H
#define SOG_GRAPHICS_H

#include <sog/math.h>

#include <stdint.h>

namespace sog {

union color
{
	color() = default;

	template<typename Ty>
	color( const sog::vec4<Ty>& _vec )
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

typedef void( *shader_main_t )( sog::vec4f& _out, sog::vec2f _in );

void clear( Context* _pContext, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a );

void runShader( KernelList* _kernels, shader_main_t _shader );

}

}

#endif
