#ifndef SOG_CONTEXT
#define SOG_CONTEXT

#include <stdint.h>

struct SDL_Window;
struct SDL_Surface;

struct SogContext
{

	SDL_Window* pWindow = nullptr;
	SDL_Surface* pWindowSurface = nullptr;
	SDL_Surface* pBackBuffer = nullptr;

	uint32_t width;
	uint32_t height;

};

SogContext sogInitializeContext( uint32_t _width, uint32_t _height );
void sogShutdownContext( SogContext* _pContext );

uint32_t sogMapRGBA( SogContext* _pContext, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a );

void sogBeginDraw( SogContext* _pContext );
void sogEndDraw( SogContext* _pContext );

#endif