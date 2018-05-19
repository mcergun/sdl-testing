#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include <WordList.h>
#include <SDLTextRenderer.h>
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

	SDL_version compVersion;
	const SDL_version *linkVersion = TTF_Linked_Version();
	SDL_TTF_VERSION(&compVersion);
	cout << std::to_string(compVersion.major) << "." <<
		std::to_string(compVersion.minor) << "." <<
		std::to_string(compVersion.patch) << endl;
	cout << std::to_string(linkVersion->major) << "." <<
		std::to_string(linkVersion->minor) << "." <<
		std::to_string(linkVersion->patch) << endl;

	cout << "SDL initializations are successful" << endl;
	SDLTextRenderer renderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//renderer.Initialize();

	GameLogic game;
	game.SetRenderer(&renderer);

	game.MainGame();

	SDL_Delay(2000);

	cin.get();

	return 0;
}