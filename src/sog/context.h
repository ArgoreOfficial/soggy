#ifndef SOG_CONTEXT
#define SOG_CONTEXT

#include <stdint.h>

struct SDL_Window;
struct SDL_Surface;

namespace sog {

struct Context
{
	SDL_Window* pWindow = nullptr;
	SDL_Surface* pWindowSurface = nullptr;
	SDL_Surface* pBackBuffer = nullptr;

	uint32_t width;
	uint32_t height;
};

Context initializeContext( uint32_t _width, uint32_t _height );
void shutdownContext( sog::Context* _pContext );

uint32_t mapRGBA( sog::Context* _pContext, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a );

void beginDraw( sog::Context* _pContext );
void endDraw( sog::Context* _pContext );

void swapBuffers( sog::Context* _pContext );

}

#endif