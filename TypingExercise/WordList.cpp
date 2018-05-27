#include <WordList.h>
#include <fstream>
#include <ctime>

WordList::WordList()
{
	// reserve room for at least 10 words
	activeWords.reserve(10);
	wordMatches.reserve(10);
	srand(time(NULL));
}

void WordList::ReadFile(std::string path)
{
	std::ifstream fs;
	fs.open(path, std::ios_base::in);
	if (fs.is_open())
	{
		std::string tmp;
		while (fs >> tmp)
		{
			dictionary.push_back(tmp);
		}
	}
}

void WordList::SetWordTypedNotifier(WordTyped func)
{
	if (func)
		wordTyped = func;
}

void WordList::SetMutex(std::mutex * mtx)
{
	listMutex = mtx;
}

std::string WordList::GetRandomWord()
{
	size_t idx = rand() % dictionary.size();
	return dictionary[idx];
}

WordList & WordList::AddWord(std::string word)
{
	activeWords.push_back(word);
	wordMatches.push_back(false);
	return *this;
}

bool WordList::DoesCharMatch(const char c)
{
	bool foundInList = false;
	compareBuf[bufIdx++] = c;
	for (size_t i = 0; i < activeWords.size(); ++i)
	{
		wordMatches[i] = activeWords[i].find(compareBuf) == 0;
		foundInList |= wordMatches[i];
		if (wordMatches[i] && activeWords[i].length() == bufIdx)
		{
			// a full word is typed
			if (wordTyped)
				wordTyped(i);
			memset(compareBuf, 0, bufIdx);
			bufIdx = 0;
			break;
		}
	}
	return foundInList;
}

WordList & WordList::EraseLastCharacter()
{
	if (bufIdx > 0)
	{
		compareBuf[--bufIdx] = 0;
	}
	return *this;
}

size_t WordList::GetWordCount() const
{
	return activeWords.size();
}

void WordList::RemoveWordAtIdx(size_t idx)
{
	if (idx < activeWords.size())
	{
		activeWords.erase(activeWords.begin() + idx);
		wordMatches.erase(wordMatches.begin() + idx);
	}
}

std::string WordList::GetCompareBuffer()
{
	return std::string(compareBuf);
}
