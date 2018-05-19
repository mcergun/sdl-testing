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

	WordList list;
	list.AddWord("word1");
	list.AddWord("word2");
	list.AddWord("word3");
	cout << "Hello world!" << endl;
	DEBUG_PRINT(list.DoesCharMatch('w'));
	DEBUG_PRINT(list.DoesCharMatch('o'));
	DEBUG_PRINT(list.DoesCharMatch('r'));
	DEBUG_PRINT(list.DoesCharMatch('d'));
	DEBUG_PRINT(list.DoesCharMatch('0'));
	DEBUG_PRINT(list.DoesCharMatch('1'));
	list.EraseLastCharacter().EraseLastCharacter();
	DEBUG_PRINT(list.DoesCharMatch('1'));
	list.EraseLastCharacter();
	DEBUG_PRINT(list.DoesCharMatch('2'));

	SDLTextRenderer renderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDLInputHandler input;
	//renderer.Initialize();

	GameLogic game;
	game.SetRenderer(&renderer);
	game.SetInputHandler(&input);

	game.MainGame();

	SDL_Delay(2000);

	cin.get();

	return 0;
}