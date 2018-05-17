#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

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
	TextRenderer();
	TextRenderer(int flags);
	~TextRenderer();
	int Initialize();
	void Reset();
	int AddWord(std::string text);
	void MoveWord(size_t wordIdx, MoveDirection direction, int amount);
	void MoveAllWords(MoveDirection direction, int amount);
	void MoveWord(size_t wordIdx, int x, int y);
	void MoveAllWords(int x, int y);
	void RemoveWordAtIdx(size_t idx);
	int DrawAllWords();

private:
	SDL_Texture * CreateTexture(std::string text);
	int DrawTexture(SDL_Texture *texture, SDL_Rect *rect, bool instant = false, bool clear = false);
	int DrawSurface(SDL_Surface *surface, SDL_Rect *rect, bool instant = false, bool clear = false);

	SDL_Renderer *renderer;
	SDL_Window *win;
	TTF_Font *font;
	std::string fontPath = "./fonts/FreeMono.otf";
	std::vector<SDL_Texture *> textures;
	std::vector<SDL_Rect> textureSizes;
	std::vector<int> textureLocs;
	size_t totalCount = 0;
	size_t screenCapacity = 0;
	int flags;

	const int winWidth = 800;
	const int winHeight = 600;
	const int fontHeight = 16;
};
#endif