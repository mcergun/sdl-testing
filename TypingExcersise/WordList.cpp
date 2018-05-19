#include <WordList.h>

WordList::WordList()
{
	// reserve room for at least 10 words
	words.reserve(10);
	wordMatches.reserve(10);
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
	}

	if (found)
	{
		// something should be done if compareBuf length matches with the match's length
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
