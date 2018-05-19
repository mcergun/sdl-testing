#include "SDLInputHandler.h"

SDLInputHandler::SDLInputHandler()
{
}


SDLInputHandler::~SDLInputHandler()
{
}

int SDLInputHandler::Initialize()
{
	int ret = 0;
	if (!(SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_EVERYTHING))
	{
		ret |= SDL_Init(SDL_INIT_EVERYTHING);
	}
	return ret;
}

int SDLInputHandler::ReadKey()
{
	int ret = 0;
	ret = SDL_PollEvent(&e);
	if (ret)
		SDL_Delay(500);
	return ret;
}
