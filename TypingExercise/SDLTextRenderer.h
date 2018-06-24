#ifndef _SDL_TEXT_RENDERER_H_
#define _SDL_TEXT_RENDERER_H_

#include <vector>
#include <string>
#include <mutex>
#include <SDL.h>
#include <SDL_ttf.h>
#include <TextRenderer.h>

struct WordTexture
{
	SDL_Texture *texture;
	SDL_Rect size;
	size_t usedRoute;
};

class SDLTextRenderer : public TextRenderer
{
public:
	SDLTextRenderer(std::string path, unsigned int size);
	SDLTextRenderer(std::string path, unsigned int size, int flags);
	~SDLTextRenderer();
	int Initialize();
	void Reset();
	void CloseWindow();
	int AddWord(std::string text, Color color);
	int AddWordAt(std::string text, int x, int y, Color color);
	void MoveWord(size_t wordIdx, MoveDirection direction, int amount);
	void MoveAllWords(MoveDirection direction, int amount);
	void MoveWord(size_t wordIdx, int x, int y);
	void MoveAllWords(int x, int y);
	void RemoveWordAtIdx(size_t idx);
	int DrawAllWords();
	int UpdateScore(int newScore);
	int UpdateWrittenWord(std::string word);

	static SDL_Color ConvertColorToSDL(Color color);

private:
	SDLTextRenderer();
	SDL_Texture * CreateTexture(std::string text, Color color = ColorWhite);
	int DrawTexture(SDL_Texture *texture, SDL_Rect *rect, bool instant = false, bool clear = false);
	int DrawSurface(SDL_Surface *surface, SDL_Rect *rect, bool instant = false, bool clear = false);
	inline bool IsRectOutOfBounds(SDL_Rect *rect);
	inline bool IsRouteClear(size_t wayIdx);
	void CalculateSizeParameters(SDL_Rect &rect);

	SDL_Renderer *renderer = nullptr;
	SDL_Window *win = nullptr;
	TTF_Font *font = nullptr;
	std::mutex *listMutex = nullptr;
	SDL_Texture *typingTexture;
	SDL_Texture *scoreTexture;
	SDL_Rect typingPos;
	SDL_Rect scorePos;

	std::vector<WordTexture> words;
	// Keeps routes' status as available or not, used to spawn textures at
	// pseudo-random locations
	std::vector<bool> textureRouteAvailablity;
	size_t totalCount = 0;
	size_t screenCapacity = 0;
	int flags;
	// TODO: Make following variables editable at run-time
	int winWidth = 800;
	int winHeight = 600;
};
#endif