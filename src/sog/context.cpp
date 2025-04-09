#include "context.h"

#include <SDL.h>

sog::Context sog::initializeContext( uint32_t _width, uint32_t _height )
{
	SDL_Init( SDL_INIT_EVERYTHING );

	sog::Context context{};

	context.width  = _width;
	context.height = _height;

	context.pWindow        = SDL_CreateWindow( "Soggy!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0 );
	context.pWindowSurface = SDL_GetWindowSurface( context.pWindow );
	context.pBackBuffer    = SDL_CreateRGBSurfaceWithFormat( 0, _width, _height, 0, context.pWindowSurface->format->format );

	return context;
}

void sog::shutdownContext( sog::Context* _pContext )
{
	SDL_FreeSurface( _pContext->pBackBuffer );
	SDL_DestroyWindow( _pContext->pWindow );

	SDL_Quit();
}

uint32_t sog::mapRGBA( sog::Context* _pContext, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a )
{
	return SDL_MapRGBA( _pContext->pWindowSurface->format, _r, _g, _b, _a );
}

void sog::beginDraw( sog::Context* _pContext )
{
	SDL_LockSurface( _pContext->pBackBuffer );
}

void sog::endDraw( sog::Context* _pContext )
{
	SDL_UnlockSurface( _pContext->pBackBuffer );
}

void sog::swapBuffers( sog::Context* _pContext )
{
	SDL_BlitSurface( _pContext->pBackBuffer, 0, _pContext->pWindowSurface, 0 );
	SDL_UpdateWindowSurface( _pContext->pWindow );
}

