#include "SDLTextRenderer.h"

SDLTextRenderer::SDLTextRenderer()
{

}

SDLTextRenderer::SDLTextRenderer(int flags) :
	flags(flags)
{
}

SDLTextRenderer::~SDLTextRenderer()
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

int SDLTextRenderer::Initialize()
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
				font = TTF_OpenFont(fontPath.c_str(), fontHeight);
				if (font)
					ret = 0;
			}
		}
	}
	return ret;
}

void SDLTextRenderer::Reset()
{
	for (auto itm : textures)
	{
		SDL_DestroyTexture(itm);
	}
	textures.clear();
	textureSizes.clear();
	textureLocs.clear();
	totalCount = 0;
}

int SDLTextRenderer::AddWord(std::string text)
{
	if (!text.empty())
	{
		SDL_Texture *texture = CreateTexture(text);
		SDL_Rect rect{ 0,0,0,0 };
		if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == 0)
		{
			if (screenCapacity == 0)
			{
				screenCapacity = winHeight / rect.h;
			}
			rect.y = (totalCount % screenCapacity) * rect.h;
			rect.x = -rect.w;
			textureSizes.push_back(rect);
			textures.push_back(texture);
			totalCount++;
		}
	}
	return 0;
}

void SDLTextRenderer::MoveWord(size_t wordIdx, MoveDirection direction, int amount)
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

void SDLTextRenderer::MoveAllWords(MoveDirection direction, int amount)
{
	for (size_t i = 0; i < textures.size(); ++i)
	{
		MoveWord(i, direction, amount);
	}
}

void SDLTextRenderer::MoveWord(size_t wordIdx, int x, int y)
{
	if (wordIdx < textures.size())
	{
		textureSizes[wordIdx].x = x;
		textureSizes[wordIdx].y = y;
	}
}

void SDLTextRenderer::MoveAllWords(int x, int y)
{
	for (size_t i = 0; i < textures.size(); ++i)
	{
		MoveWord(i, x, y);
	}
}

void SDLTextRenderer::RemoveWordAtIdx(size_t idx)
{
	if (idx < textures.size())
	{
		textures.erase(textures.begin() + idx);
		textureSizes.erase(textureSizes.begin() + idx);
	}
}

SDL_Texture * SDLTextRenderer::CreateTexture(std::string text)
{
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(),
		SDL_Color{ 255, 255, 255, 255 });
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;

}

int SDLTextRenderer::DrawTexture(SDL_Texture *texture, SDL_Rect *rect, bool instant, bool clear)
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

int SDLTextRenderer::DrawSurface(SDL_Surface *surface, SDL_Rect *rect, bool instant, bool clear)
{
	int ret = -1;
	SDL_Texture *texture = nullptr;
	if (renderer && surface)
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture)
	{
		ret = DrawTexture(texture, rect, instant, clear);
		SDL_FreeSurface(surface);
	}
	return ret;
}

int SDLTextRenderer::DrawAllWords()
{
	int ret = -1;
	if (textures.size() > 0)
	{
		ret = DrawTexture(textures[0], &textureSizes[0], false, true);
		for (size_t i = 1; i < textures.size() - 1; ++i)
		{
			ret |= DrawTexture(textures[i], &textureSizes[i]);
		}
		ret |= DrawTexture(textures[textures.size() - 1], &textureSizes[textures.size() - 1], true);
	}
	return ret;
}