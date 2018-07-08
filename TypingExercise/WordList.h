#ifndef _WORD_LIST_H_
#define _WORD_LIST_H_

#include <string>
#include <vector>

typedef void(*WordTyped)(size_t);

class WordList
{
public:
	WordList();
	void ReadFile(std::string path);
	void SetWordTypedNotifier(WordTyped func);
	std::string GetRandomWord();
	WordList & AddWord(std::string word);
	size_t InsertCharacter(const char c);
	size_t GetMatchingIdx();
	WordList & EraseLastCharacter();
	size_t GetWordCount() const;
	void RemoveWordAtIdx(size_t idx);
	std::string GetCompareBuffer();
	char GetLastCharacter();

	std::vector<std::string> activeWords = std::vector<std::string>();
private:
	static constexpr unsigned int DEF_COLLECTION_SIZE = 32;
	std::vector<bool>wordMatches = std::vector<bool>();
	std::vector<std::string> dictionary = std::vector<std::string>();
	char compareBuf[256] = { 0 };
	unsigned int bufIdx = 0;
	WordTyped wordTyped = nullptr;
};

#endif