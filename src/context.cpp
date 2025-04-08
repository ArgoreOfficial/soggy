#include "context.h"

#include <SDL.h>

SogContext sogInitializeContext( uint32_t _width, uint32_t _height )
{
	SDL_Init( SDL_INIT_EVERYTHING );

	SogContext context{};

	context.width  = _width;
	context.height = _height;

	context.pWindow        = SDL_CreateWindow( "Soggy!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0 );
	context.pWindowSurface = SDL_GetWindowSurface( context.pWindow );
	context.pBackBuffer    = SDL_CreateRGBSurfaceWithFormat( 0, _width, _height, 0, context.pWindowSurface->format->format );

	return context;
}

void sogShutdownContext( SogContext* _pContext )
{
	SDL_FreeSurface( _pContext->pBackBuffer );
	SDL_DestroyWindow( _pContext->pWindow );

	SDL_Quit();
}

uint32_t sogMapRGBA( SogContext* _pContext, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
	return SDL_MapRGBA( _pContext->pWindowSurface->format, _r, _g, _b, _a );
}

void sogBeginDraw( SogContext* _pContext )
{
	SDL_LockSurface( _pContext->pBackBuffer );
}

void sogEndDraw( SogContext* _pContext )
{
	SDL_UnlockSurface( _pContext->pBackBuffer );
}
