#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include <WordList.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define DEBUG_PRINT(eq) std::cout << (#eq) << " = " << (eq) << std::endl;

bool quit = false;

enum MoveDirection
{
	ToLeft,
	ToRight,
	ToDown,
	ToUp,
};

class TextRenderer
{
public:
	TextRenderer()
	{
		
	}

	TextRenderer(int flags) :
		flags(flags)
	{

	}

	~TextRenderer()
	{
		if (win)
			SDL_DestroyWindow(win);
		if (renderer)
			SDL_DestroyRenderer(renderer);
		// TODO: Enable this back
		//if (font)
		//	TTF_CloseFont(font);
		SDL_Quit();
		TTF_Quit();
	}

	int Initialize()
	{
		int ret = -1;
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0)
		{
			win = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
			if (win)
			{
				renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC);
				if (renderer)
				{
					font = TTF_OpenFont(fontPath.c_str(), 20);
					if (font)
						ret = 0;
				}
			}
		}
		return ret;
	}

	int AddWord(std::string text)
	{
		if (!text.empty())
		{
			SDL_Texture *texture = CreateTexture(text);
			if (texture)
			{
				SDL_Rect rect{ 0,0,0,0 };
				SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
				rect.y = (textures.size() * rect.h) % winHeight;
				textureSizes.push_back(rect);
				textures.push_back(texture);
			}
		}
		return 0;
	}

	void MoveWord(size_t wordIdx, MoveDirection direction, int amount)
	{
		if (wordIdx < textures.size())
		{
			switch (direction)
			{
			case ToLeft:
				textureSizes[wordIdx].x -= amount;
				break;
			case ToRight:
				textureSizes[wordIdx].x += amount;
				break;
			case ToDown:
				textureSizes[wordIdx].x -= amount;
				break;
			case ToUp:
				textureSizes[wordIdx].y += amount;
				break;
			default:
				break;
			}
		}
	}

	void MoveAllWords(MoveDirection direction, int amount)
	{
		for (size_t i = 0; i < textures.size(); ++i)
		{
			MoveWord(i, direction, amount);
		}
	}

	void MoveWord(size_t wordIdx, int x, int y)
	{
		if (wordIdx < textures.size())
		{
			textureSizes[wordIdx].x = x;
			textureSizes[wordIdx].y = y;
		}
	}

	void MoveAllWords(int x, int y)
	{
		for (size_t i = 0; i < textures.size(); ++i)
		{
			MoveWord(i, x, y);
		}
	}

	void RandomizeXLocs()
	{
		for (auto &rect : textureSizes)
		{
			rect.x = rand() % 300;
		}
	}

	SDL_Texture * CreateTexture(std::string text)
	{
		SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), 
			SDL_Color{ 255, 255, 255, 255 });
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		return texture;

	}

	int DrawTexture(SDL_Texture *texture, SDL_Rect *rect, bool instant = false, bool clear = false)
	{
		int ret = -1;
		if (renderer && texture)
		{
			if (clear)
				SDL_RenderClear(renderer);
			ret = SDL_RenderCopy(renderer, texture, nullptr, rect);
			if (instant)
				SDL_RenderPresent(renderer);
		}
		return ret;
	}

	int DrawSurface(SDL_Surface *surface, SDL_Rect *rect, bool instant = false, bool clear = false)
	{
		int ret = -1;
		SDL_Texture *texture;
		if (renderer && surface)
			texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture)
		{
			ret = DrawTexture(texture, rect, instant, clear);
			SDL_FreeSurface(surface);
		}
		return ret;
	}

	int DrawAllWords()
	{
		int ret = DrawTexture(textures[0], &textureSizes[0], false, true);
		for (size_t i = 1; i < textures.size() - 1; ++i)
		{
			ret |= DrawTexture(textures[i], &textureSizes[i]);
		}
		ret |= DrawTexture(textures[textures.size() - 1], &textureSizes[textures.size() - 1], true);
		return ret;
	}

	SDL_Renderer *renderer;
	SDL_Window *win;
	TTF_Font *font;
	std::string fontPath = "./fonts/FreeMono.otf";
	std::vector<SDL_Texture *> textures;
	std::vector<SDL_Rect> textureSizes;
	int flags;

	int winWidth = 800;
	int winHeight = 600;
};

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

	renderer.AddWord("sdhshq35hwerh");
	renderer.AddWord("sgjwsthjsdf");
	renderer.AddWord("sdfjsdfjhsdfj");
	renderer.AddWord("sdfhsd");
	renderer.AddWord("fgghg");
	renderer.AddWord("sdfgjsdfgjsdfhjsdfh");
	renderer.AddWord("fghjfghj");
	renderer.AddWord("fghkfghkfghkfghk");
	renderer.AddWord("fghkfghk");
	renderer.AddWord("fghkfghkfghkgh");
	renderer.AddWord("fgghg");
	renderer.AddWord("as");
	renderer.AddWord("fggsafhg");
	renderer.AddWord("fghkfghk");
	renderer.AddWord("fghkfghkfghkgh");
	renderer.AddWord("sdfhsd");
	renderer.AddWord("fgghg");

	renderer.RandomizeXLocs();
	for (int i = 0; i < 400; ++i)
	{
		renderer.DrawAllWords();
		renderer.MoveAllWords(ToRight, 1);
		if (i % 20 == 0)
		{
			renderer.AddWord("word" + std::to_string(rand() % 100));
		}
		SDL_Delay(40);
	}

	SDL_Delay(2000);

exiting:
	TTF_Quit();
	SDL_Quit();
	cin.get();

	return 0;
}