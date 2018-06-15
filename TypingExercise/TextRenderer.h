#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include <string>

typedef void(*WordOutOfBoundsEvent)(size_t);

enum MoveDirection
{
	ToLeft,
	ToRight,
	ToDown,
	ToUp,
};

enum Color
{
	ColorRed,
	ColorGreen,
	ColorBlue,
	ColorWhite,
	ColorBlack,
	ColorGray,
	ColorCyan,
	ColorMagenta,
	ColorYellow,
};

class TextRenderer
{
public:
	virtual ~TextRenderer() {};
	virtual int Initialize() = 0;
	virtual void Reset() = 0;
	virtual void CloseWindow() = 0;
	virtual	int AddWord(std::string text, Color color = ColorWhite) = 0;
	virtual int AddWordAt(std::string text, int x, int y, Color color = ColorWhite) = 0;
	virtual void MoveWord(size_t wordIdx, MoveDirection direction, int amount) = 0;
	virtual void MoveAllWords(MoveDirection direction, int amount) = 0;
	virtual void MoveWord(size_t wordIdx, int x, int y) = 0;
	virtual void MoveAllWords(int x, int y) = 0;
	virtual void RemoveWordAtIdx(size_t idx) = 0;
	virtual int DrawAllWords() = 0;
	virtual int UpdateWrittenWord(std::string word) = 0;
	virtual int UpdateScore(int newScore) = 0;
	virtual void SetWordOutNotifier(WordOutOfBoundsEvent func)
	{
		wordOutOfBounds = func;
	}

protected:
	WordOutOfBoundsEvent wordOutOfBounds = nullptr;
};


#endif
