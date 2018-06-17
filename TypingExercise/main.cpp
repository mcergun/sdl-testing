#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include <WordList.h>
#include <SDLTextRenderer.h>
#include <SDLInputHandler.h>
#include <GameLogic.h>

#define DEBUG_PRINT(eq) std::cout << (#eq) << " = " << (eq) << std::endl;

const std::string DEF_FONT_PATH = "./fonts/FreeMono.otf";
const unsigned int DEF_FONT_SIZE = 24;
const int DEF_FLAGS = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

bool quit = false;

int main(int argc, char **argv)
{
	using namespace std;
	std::string path = DEF_FONT_PATH;
	unsigned int size = DEF_FONT_SIZE;
	int flags = DEF_FLAGS;

	ifstream settings;
	settings.open("C:\\Users\\mert\\Documents\\Visual Studio 2017\\Projects\\TypingExercise\\x64\\Debug\\settings.txt", ifstream::in);
	if (settings.is_open())
	{
		char line[1024];
		cout << "File found" << endl;
		settings.getline(line, 1024);
		path = line;
	}
	else
	{
		cout << "File missing" << endl;
	}

	SDLTextRenderer renderer(path, size, flags);
	SDLInputHandler input;
	//renderer.Initialize();
	GameLogic game;
	game.SetRenderer(&renderer);
	game.SetInputHandler(&input);

	game.GameLoop();

	return 0;
}