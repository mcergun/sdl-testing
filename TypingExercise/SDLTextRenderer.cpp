#include "SDLTextRenderer.h"

SDLTextRenderer::SDLTextRenderer(std::string path, unsigned int size) :
	TextRenderer(path, size)
{

}

SDLTextRenderer::SDLTextRenderer(std::string path, unsigned int size, int flags) :
	TextRenderer(path, size), flags(flags)
{
}

SDLTextRenderer::~SDLTextRenderer()
{
	DestroyTexture(scoreTexture);
	DestroyTexture(typingTexture);
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
	int ret = 0;
	if (!(SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_EVERYTHING))
	{
		SDL_DisplayMode dm;
		memset(&dm, 0, sizeof(dm));
		ret |= SDL_Init(SDL_INIT_EVERYTHING);
		ret |= SDL_GetCurrentDisplayMode(0, &dm);
		auto asd = SDL_GetError();
		winWidth = dm.w / 2;
		winHeight = dm.h / 2;
		win = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
		ret |= !win;
		renderer = SDL_CreateRenderer(win, -1, flags);
		ret |= !renderer;
	}
	if (!TTF_WasInit())
	{
		if (winHeight > 900)
		{
			fontSize = fontSize * 2;
		}
		else if (winHeight > 600)
		{
			fontSize = fontSize * 1.5;
		}
		ret |= TTF_Init();
		font = TTF_OpenFont(fontPath.c_str(), fontSize);
		ret |= !font;
	}
	ret |= !(wordOutOfBounds);
	if (ret > 0)
		ret = -ret;
	return ret;
}

void SDLTextRenderer::Reset()
{
	for (auto itm : words)
	{
		SDL_DestroyTexture(itm->texture);
	}
	words.clear();
	totalCount = 0;
}

void SDLTextRenderer::CloseWindow()
{
	Reset();
	SDL_DestroyWindow(win);
}

int SDLTextRenderer::AddWord(std::string text, Color color)
{
	if (!text.empty())
	{
		SDL_Texture *texture = CreateTexture(text);
		SDL_Rect rect{ 0, 0, 0, 0 };
		if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == 0)
		{
			if (screenCapacity == 0)
			{
				CalculateSizeParameters(rect);
				UpdateScore(0);
				// Set up route statuses
				textureRouteAvailablity.reserve(screenCapacity);
				for (int i = 0; i < screenCapacity; ++i)
				{
					textureRouteAvailablity.push_back(true);
				}
			}
			bool routeFree = false;
			size_t idx = 0;
			while (!routeFree)
			{
				idx = rand() % screenCapacity;
				routeFree = textureRouteAvailablity[idx];
			}
			textureRouteAvailablity[idx] = false;
			rect.y = idx * rect.h;
			rect.x = -rect.w;
			WordTexture *word = new WordTexture;
			word->texture = texture;
			word->size = rect;
			word->usedRoute = idx;
			words.push_back(word);
			totalCount++;
		}
	}
	return 0;
}

int SDLTextRenderer::AddWordAt(std::string text, int x, int y, Color color)
{
	SDL_Texture *texture = CreateTexture(text, color);
	SDL_Rect rect{ x, y, 0, 0 };
	if (SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h) == 0)
	{
		WordTexture *word = new WordTexture;
		word->texture = texture;
		word->size = rect;
		word->usedRoute = 0;
		words.push_back(word);
	}
	int ret = 0;
	return ret;
}

void SDLTextRenderer::MoveWord(size_t wordIdx, MoveDirection direction, int amount)
{
	if (wordIdx < words.size())
	{
		switch (direction)
		{
		case ToLeft:
			words[wordIdx]->size.x -= amount;
			break;
		case ToRight:
			words[wordIdx]->size.x += amount;
			break;
		case ToDown:
			words[wordIdx]->size.x -= amount;
			break;
		case ToUp:
			words[wordIdx]->size.y += amount;
			break;
		default:
			break;
		}
		// ugly, nasty, disgusting way to solve a big problem like this
		// if equal is changed into a greater than sign, then this check succeeds every time
		// leading to textures resetting route to available even though it has been set to
		// unavailable by a new word in a previous frame.
		if (words[wordIdx]->size.x < 30)
		{
			textureRouteAvailablity[words[wordIdx]->usedRoute] = false;
		}
		else if (words[wordIdx]->size.x == 30)
		{
			textureRouteAvailablity[words[wordIdx]->usedRoute] = true;
		}

		if (IsRectOutOfBounds(&words[wordIdx]->size))
		{
			wordOutOfBounds(wordIdx);
		}
	}
}

void SDLTextRenderer::MoveAllWords(MoveDirection direction, int amount)
{
	for (size_t i = 0; i < words.size(); ++i)
	{
		MoveWord(i, direction, amount);
	}
	if (overlay.texture)
	{
		switch (direction)
		{
		case ToLeft:
			overlay.size.x -= amount;
			break;
		case ToRight:
			overlay.size.x += amount;
			break;
		case ToDown:
			overlay.size.x -= amount;
			break;
		case ToUp:
			overlay.size.y += amount;
			break;
		default:
			break;
		}
	}
}

void SDLTextRenderer::MoveWord(size_t wordIdx, int x, int y)
{
	if (wordIdx < words.size())
	{
		words[wordIdx]->size.x = x;
		words[wordIdx]->size.y = y;
		if (IsRectOutOfBounds(&words[wordIdx]->size))
		{
			wordOutOfBounds(wordIdx);
		}
	}
}

void SDLTextRenderer::MoveAllWords(int x, int y)
{
	for (size_t i = 0; i < words.size(); ++i)
	{
		MoveWord(i, x, y);
	}
}

void SDLTextRenderer::RemoveWordAtIdx(size_t idx)
{
	if (idx < words.size())
	{
		if (words[idx]->size.x < 30)
		{
			textureRouteAvailablity[words[idx]->usedRoute] = true;
		}
		delete words[idx];
		words.erase(words.begin() + idx);
	}
}

SDL_Texture * SDLTextRenderer::CreateTexture(std::string text, Color color)
{
	SDL_Color c = ConvertColorToSDL(color);
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), c);
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
		{
			ret |= SDL_RenderCopy(renderer, typingTexture, nullptr, &typingPos);
			ret |= SDL_RenderCopy(renderer, scoreTexture, nullptr, &scorePos);
			SDL_RenderPresent(renderer);
		}
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

bool SDLTextRenderer::IsRectOutOfBounds(SDL_Rect * rect)
{
	bool ret = (rect->x > winWidth) || (rect->y > winHeight);
	return ret;
}

inline bool SDLTextRenderer::IsRouteClear(size_t wayIdx)
{
	return false;
}

void SDLTextRenderer::CalculateSizeParameters(SDL_Rect &rect)
{
	screenCapacity = winHeight / rect.h - 2;
	typingPos.x = 10;
	typingPos.y = (screenCapacity + 1) * rect.h;
	scorePos.x = winWidth - 20;
	scorePos.y = (screenCapacity + 1) * rect.h;
}

void SDLTextRenderer::DestroyTexture(SDL_Texture *&text)
{
	if (text)
	{
		SDL_DestroyTexture(text);
		text = nullptr;
	}
}

int SDLTextRenderer::DrawAllWords()
{
	int ret = -1;
	if (words.size() > 1)
	{
		ret = DrawTexture(words[0]->texture, &words[0]->size, false, true);
		for (size_t i = 1; i < words.size() - 1; ++i)
		{
			ret |= DrawTexture(words[i]->texture, &words[i]->size);
		}
		if (overlay.texture != nullptr)
			ret |= DrawTexture(overlay.texture, &overlay.size);
		ret |= DrawTexture(words[words.size() - 1]->texture, &words[words.size() - 1]->size, true);
		SDL_Delay(1);
	}
	else if (words.size() == 1)
	{
		ret = DrawTexture(words[0]->texture, &words[0]->size, true, true);
		SDL_Delay(1);
	}
	return ret;
}

int SDLTextRenderer::UpdateScore(int newScore)
{
	DestroyTexture(scoreTexture);
	scoreTexture = CreateTexture("Score: " + std::to_string(newScore));
	SDL_QueryTexture(scoreTexture, nullptr, nullptr, &scorePos.w, &scorePos.h);
	if (scorePos.x + scorePos.w + 10 != winWidth)
	{
		scorePos.x = winWidth - scorePos.w - 10;
	}
	return 0;
}

int SDLTextRenderer::UpdateWrittenWord(std::string word)
{
	DestroyTexture(typingTexture);
	typingTexture = CreateTexture(word);
	SDL_QueryTexture(typingTexture, nullptr, nullptr, &typingPos.w, &typingPos.h);
	return 0;
}

int SDLTextRenderer::UpdateWordOverlay(size_t underIdx, std::string typedWord)
{
	DestroyTexture(overlay.texture);
	if (underIdx != -1)
	{
		overlay.texture = CreateTexture(typedWord, ColorRed);
		SDL_QueryTexture(overlay.texture, nullptr, nullptr, &overlay.size.w, &overlay.size.h);
		overlay.size.x = words[underIdx]->size.x;
		overlay.size.y = words[underIdx]->size.y;
	}
	return 0;
}

inline SDL_Color SDLTextRenderer::ConvertColorToSDL(Color color)
{
	SDL_Color ret{ 0, 0, 0, 0 };
	switch (color)
	{
	case ColorRed:
		ret.r = 255;
		break;
	case ColorGreen:
		ret.g = 255;
		break;
	case ColorBlue:
		ret.b = 255;
		break;
	case ColorWhite:
		ret.r = 255;
		ret.g = 255;
		ret.b = 255;
		break;
	case ColorBlack:
		break;
	case ColorGray:
		ret.r = 128;
		ret.g = 128;
		ret.b = 128;
		break;
	case ColorCyan:
		ret.g = 255;
		ret.b = 255;
		break;
	case ColorMagenta:
		ret.r = 255;
		ret.b = 255;
		break;
	case ColorYellow:
		ret.r = 255;
		ret.g = 255;
		break;
	default:
		break;
	}
	return ret;
}
