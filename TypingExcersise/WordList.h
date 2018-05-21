#ifndef _WORD_LIST_H_
#define _WORD_LIST_H_

#include <string>
#include <vector>

typedef void(*WordTyped)(size_t);

class WordList
{
public:
	WordList();
	void SetWordTypedNotifier(WordTyped func);
	WordList & AddWord(std::string word);
	bool DoesCharMatch(const char c);
	WordList & EraseLastCharacter();
	size_t GetWordCount() const;
	void RemoveWordAtIdx(size_t idx);
	std::vector<std::string> words = std::vector<std::string>();
private:
	std::vector<bool>wordMatches = std::vector<bool>();
	char compareBuf[256] = { 0 };
	unsigned int bufIdx = 0;
	WordTyped wordTyped = nullptr;
};

#endif