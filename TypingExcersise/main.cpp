#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include <WordList.h>
#include <TextRenderer.h>

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
	TextRenderer renderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer.Initialize();
	SDL_Color color = { 0xaa, 0xaa, 0xaa };
	SDL_Surface *textSurface;

	//renderer.RandomizeXLocs();
	for (int i = 0; i < 1600; ++i)
	{
		renderer.DrawAllWords();
		renderer.MoveAllWords(ToRight, 1);
		if (i % 20 == 0)
		{
			renderer.AddWord("word" + std::to_string(rand() % 999));
		}
		//if (i > 200)
		//{
		//	if (i % 28 == 1)
		//	{
		//		if (renderer.textures.size() > 0)
		//			renderer.RemoveWordAtIdx(rand() % (renderer.textures.size() / 2));
		//	}
		//}
		SDL_Delay(1);
	}

	SDL_Delay(2000);

exiting:
	TTF_Quit();
	SDL_Quit();
	cin.get();

	return 0;
}