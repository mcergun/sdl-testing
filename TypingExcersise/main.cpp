#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

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
		SDL_Window *win = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 810, SDL_WINDOW_SHOWN);
		SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


		std::vector<std::string> words;
		words.push_back("sdhshq35hwerh");
		words.push_back("sgjwsthjsdf");
		words.push_back("sdfjsdfjhsdfj");
		words.push_back("sdfhsd");
		words.push_back("fgghg");
		words.push_back("sdfgjsdfgjsdfhjsdfh");
		words.push_back("fghjfghj");
		words.push_back("fghkfghkfghkfghk");
		words.push_back("fghkfghk");
		words.push_back("fghkfghkfghkgh");
		words.push_back("fgghg");
		words.push_back("as");
		words.push_back("fggsafhg");
		words.push_back("fghkfghk");
		words.push_back("fghkfghkfghkgh");
		words.push_back("sdfhsd");
		words.push_back("fgghg");

		std::vector<SDL_Rect> rects;
		std::vector<SDL_Texture *> textTextures;
		std::vector<double> positions;
		rects.reserve(words.size());
		textTextures.reserve(words.size());

		for (int i = 0; i < words.size(); ++i)
		{
			rects.push_back(SDL_Rect{ rand() % 500, i * 40, 0, 0 });
			positions.push_back(rand() % 500);
		}

		for (int i = 0; i < words.size(); i++)
		{
			textSurface = TTF_RenderText_Blended(font, words[i].c_str(), color);
			SDL_Texture *tmpTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (textSurface && tmpTexture)
			{
				textTextures.push_back(tmpTexture);
				SDL_QueryTexture(tmpTexture, nullptr, nullptr, &rects[i].w, &rects[i].h);
			}
			SDL_FreeSurface(textSurface);
			textSurface = nullptr;
		}

		for (int i = 0; i < 1200; i += 1)
		{
			SDL_RenderClear(renderer);
			for (int j = 0; j < words.size(); ++j)
			{
				positions[j] = positions[j] * 0.001 + positions[j] + 0.3;
				rects[j].x = positions[j];

				SDL_RenderCopy(renderer, textTextures[j], nullptr, &rects[j]);
			}
			SDL_RenderPresent(renderer);
		}

		SDL_Rect rect = { 0, 0, 200, 200 };
		SDL_QueryTexture(textTextures[0], nullptr, nullptr, &rect.w, &rect.h);
		for (int i = 0; i < 800; i += 1)
		{
			rect.x = i;
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, textTextures[0], nullptr, &rect);
			SDL_RenderPresent(renderer);
		}
		SDL_Delay(1000);
		TTF_CloseFont(font);
		SDL_DestroyTexture(textTextures[0]);
		SDL_DestroyRenderer(renderer);
	}

exiting:
	TTF_Quit();
	SDL_Quit();
	cin.get();

	return 0;
}