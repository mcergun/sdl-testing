#include <WordList.h>

WordList::WordList()
{
	// reserve room for at least 10 words
	words.reserve(10);
	wordMatches.reserve(10);
}

void WordList::SetWordTypedNotifier(WordTyped func)
{
	if (func)
		wordTyped = func;
}

WordList & WordList::AddWord(std::string word)
{
	bool found = false;
	for (unsigned int i = 0; !found && i < words.size(); ++i)
	{
		found = words[i] == word;
	}

	if (!found)
	{
		words.push_back(word);
		wordMatches.push_back(false);
	}
	return *this;
}

bool WordList::DoesCharMatch(const char c)
{
	bool found = false;
	compareBuf[bufIdx++] = c;
	for (size_t i = 0; i < words.size(); ++i)
	{
		wordMatches[i] = words[i].find(compareBuf) == 0;
		found |= wordMatches[i];
		if (found && words[i].length() == bufIdx)
		{
			// a full word is typed
			if (wordTyped)
				wordTyped(i);
			memset(compareBuf, 0, bufIdx);
			bufIdx = 0;
			break;
		}
	}
	return found;
}

WordList & WordList::EraseLastCharacter()
{
	if (bufIdx > 0)
	{
		compareBuf[bufIdx--] = 0;
	}
	return *this;
}

size_t WordList::GetWordCount() const
{
	return words.size();
}

void WordList::RemoveWordAtIdx(size_t idx)
{
	if (idx < words.size())
	{
		words.erase(words.begin() + idx);
	}
}
