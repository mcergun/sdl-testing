#include <WordList.h>
#include <fstream>
#include <ctime>
#include <cstring>

WordList::WordList()
{
	// reserve room for at least 10 words
	activeWords.reserve(DEF_COLLECTION_SIZE);
	wordMatches.reserve(DEF_COLLECTION_SIZE);
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
	fs.clear();
	fs.close();
}

void WordList::SetWordTypedNotifier(WordTyped func)
{
	if (func)
		wordTyped = func;
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

size_t WordList::InsertCharacter(const char c)
{
	compareBuf[bufIdx++] = c;
	return bufIdx;
}

size_t WordList::GetMatchingIdx()
{
	bool foundInList = false;
	size_t pos = -1;
	size_t smallestSize = -1;
	for (size_t i = 0; i < activeWords.size(); ++i)
	{
		if (activeWords[i].find(compareBuf) == 0)
		{
			size_t wordLen = activeWords[i].length();
			if (wordLen == bufIdx)
			{
				// word fully matches
				if (wordTyped)
					wordTyped(i);
				memset(compareBuf, 0, bufIdx);
				bufIdx = 0;
				break;
			}
			if (wordLen < smallestSize)
			{
				smallestSize = wordLen;
				pos = i;
			}
		}
	}
	return pos;
	//for (size_t i = 0; i < activeWords.size(); ++i)
	//{
	//	wordMatches[i] = activeWords[i].find(compareBuf) == 0;
	//	foundInList |= wordMatches[i];
	//	if (wordMatches[i] && activeWords[i].length() == bufIdx)
	//	{
	//		// a full word is typed
	//		if (wordTyped)
	//			wordTyped(i);
	//		memset(compareBuf, 0, bufIdx);
	//		bufIdx = 0;
	//		break;
	//	}
	//}
	//return foundInList;
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

char WordList::GetLastCharacter()
{
	return compareBuf[bufIdx - 1];
}
