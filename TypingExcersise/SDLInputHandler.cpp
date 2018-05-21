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
	if (ret && e.type == SDL_KEYDOWN)
	{
		ret = e.key.keysym.sym;
	}
	else
	{
		ret = 0;
	}
	return ret;
}

char SDLInputHandler::KeyToVisualChar(int enumCode)
{
	SDL_Keycode key = static_cast<SDL_Keycode>(enumCode);

	return 0;
}
