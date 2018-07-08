#ifndef _SDL_INPUT_HANDLER_H_
#define _SDL_INPUT_HANDLER_H_

#include <SDL.h>
#include <InputHandler.h>

class SDLInputHandler : public InputHandler
{
public:
	SDLInputHandler();
	~SDLInputHandler();
	int Initialize();
	int ReadKey();
private:
	SDL_Event e;
};

#endif