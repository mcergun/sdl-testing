#ifndef _SDL_TEXT_RENDERER_H_
#define _SDL_TEXT_RENDERER_H_

#include <vector>
#include <string>
#include <mutex>
#include <SDL.h>
#include <SDL_ttf.h>
#include <TextRenderer.h>

class SDLTextRenderer : public TextRenderer
{
public:
	SDLTextRenderer();
	SDLTextRenderer(int flags);
	~SDLTextRenderer();
	int Initialize();
	void Reset();
	int AddWord(std::string text);
	void MoveWord(size_t wordIdx, MoveDirection direction, int amount);
	void MoveAllWords(MoveDirection direction, int amount);
	void MoveWord(size_t wordIdx, int x, int y);
	void MoveAllWords(int x, int y);
	void RemoveWordAtIdx(size_t idx);
	int DrawAllWords();
	int UpdateWrittenWord(std::string word);

private:
	SDL_Texture * CreateTexture(std::string text);
	int DrawTexture(SDL_Texture *texture, SDL_Rect *rect, bool instant = false, bool clear = false);
	int DrawSurface(SDL_Surface *surface, SDL_Rect *rect, bool instant = false, bool clear = false);
	inline bool IsRectOutOfBounds(SDL_Rect *rect);
	inline bool IsRouteClear(size_t wayIdx);

	SDL_Renderer *renderer = nullptr;
	SDL_Window *win = nullptr;
	TTF_Font *font = nullptr;
	std::string fontPath = "./fonts/FreeMono.otf";
	std::mutex *listMutex = nullptr;
	SDL_Texture *typingTexture;
	SDL_Rect typingPos;
	std::vector<SDL_Texture *> textures;
	std::vector<SDL_Rect> textureSizes;
	std::vector<size_t> textureUsedRoutes;
	std::vector<int> textureLocs;
	std::vector<bool> textureRouteAvailablity;
	size_t totalCount = 0;
	size_t screenCapacity = 0;
	int flags;

	const int winWidth = 800;
	const int winHeight = 600;
	int fontHeight = 24;
};
#endif