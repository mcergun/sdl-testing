#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include <WordList.h>
#include <SDLTextRenderer.h>
#include <SDLInputHandler.h>
#include <GameLogic.h>

#define DEBUG_PRINT(eq) std::cout << (#eq) << " = " << (eq) << std::endl;

bool quit = false;

int main(int argc, char **argv)
{
	using namespace std;

	SDLTextRenderer renderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDLInputHandler input;
	//renderer.Initialize();

	GameLogic game;
	game.SetRenderer(&renderer);
	game.SetInputHandler(&input);

	game.GameLoop();

	return 0;
}