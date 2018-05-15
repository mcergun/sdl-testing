#include <iostream>
#include <string>
#include <vector>

#include <WordList.h>
#include <SDL.h>
#include <SDL_ttf.h>

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

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0)
	{
		goto exiting;
	}
	else
	{
		cout << "SDL initializations are successful" << endl;
		auto fontPath = "./fonts/FreeSans.otf";
		TTF_Font *font = TTF_OpenFont(fontPath, 24);
		if (!font)
		{
			cout << "Can't load " << fontPath << endl;
			cout << "Error = " << TTF_GetError() << endl;
		}
		SDL_Color color = { 0xaa, 0xaa, 0xaa };
		SDL_Surface *textSurface;
		SDL_Window *win = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_SHOWN);
		SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_Rect rect = { 0, 0, 200, 200 };
		textSurface = TTF_RenderText_Blended(font, "Hello World!", color);
		SDL_Texture *textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTex, nullptr, nullptr, &rect.w, &rect.h);
		for (int i = 0; i < 1600; i += 1)
		{
			rect.x = i / 2;
			rect.y = i / 4;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, textTex, nullptr, &rect);
			SDL_RenderPresent(renderer);
			SDL_Delay(8);
		}
		SDL_Delay(3000);
		TTF_CloseFont(font);
		SDL_FreeSurface(textSurface);
		SDL_DestroyRenderer(renderer);
	}

exiting:
	TTF_Quit();
	SDL_Quit();
	cin.get();

	return 0;
}