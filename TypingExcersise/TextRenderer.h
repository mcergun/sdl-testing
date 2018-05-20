#ifndef _TEXT_RENDERER_H_
#define _TEXT_RENDERER_H_

#include <string>

typedef void(*WordOutOfBounds)(size_t);

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
	virtual ~TextRenderer() {};
	virtual int Initialize() = 0;
	virtual void Reset() = 0;
	virtual	int AddWord(std::string text) = 0;
	virtual void MoveWord(size_t wordIdx, MoveDirection direction, int amount) = 0;
	virtual void MoveAllWords(MoveDirection direction, int amount) = 0;
	virtual void MoveWord(size_t wordIdx, int x, int y) = 0;
	virtual void MoveAllWords(int x, int y) = 0;
	virtual void RemoveWordAtIdx(size_t idx) = 0;
	virtual int DrawAllWords() = 0;
	virtual void SetWordOutNotifier(WordOutOfBounds func) = 0;
};


#endif
