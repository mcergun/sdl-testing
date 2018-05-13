#include <iostream>
#include <string>
#include <vector>

#include <WordList.h>
#include <SDL.h>

#define DEBUG_PRINT(eq) std::cout << (#eq) << " = " << (eq) << std::endl;

int initSDL();
int closeSDL();

const int WIDTH = 960;
const int HEIGHT = 540;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event e;
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

	if (!initSDL())
	{
		//SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		//SDL_RenderClear(renderer);
		//SDL_RenderPresent(renderer);
		SDL_Surface *surf = SDL_LoadBMP("C:\\Users\\mert\\Pictures\\youtd.BMP");
		if (surf)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
			SDL_FreeSurface(surf);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
			SDL_RenderPresent(renderer);

			while (!quit)
			{
				while (!SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
			}
			SDL_DestroyTexture(texture);
			closeSDL();
		}
		cin.get();
	}

	return 0;
}

int initSDL()
{
	int ret = -1;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (window)
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				ret = 0;
			}
		}
	}
	return ret;
}

int closeSDL()
{

	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}