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
	{
		if (e.type == SDL_KEYDOWN)
		{
			ret = e.key.keysym.sym;
			switch (e.key.keysym.sym)
			{
			case SDLK_BACKSPACE:
				if (backspacePressed)
					backspacePressed();
				break;
			case SDLK_RETURN:
			case SDLK_RETURN2:
			case SDLK_KP_ENTER:
				if (enterPressed)
					enterPressed();
				break;
			case SDLK_UP:
				if (arrowKeyPressed)
					arrowKeyPressed(ArrowUp);
				break;
			case SDLK_DOWN:
				if (arrowKeyPressed)
					arrowKeyPressed(ArrowDown);
				break;
			case SDLK_RIGHT:
				if (arrowKeyPressed)
					arrowKeyPressed(ArrowRight);
				break;
			case SDLK_LEFT:
				if (arrowKeyPressed)
					arrowKeyPressed(ArrowLeft);
				break;
			case SDLK_ESCAPE:
			case SDLK_PAUSE:
				if (pauseRequested)
					pauseRequested();
				break;
			default:
				if (visualPressed)
					visualPressed(e.key.keysym.sym);
				break;
			}
		}
		else if (e.type == SDL_QUIT)
		{
			if (exitRequested)
				exitRequested();
		}
	}
	else
	{
		ret = 0;
	}
	return ret;
}
