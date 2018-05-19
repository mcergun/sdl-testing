#include "GameLogic.h"

GameLogic::GameLogic()
{
}


GameLogic::~GameLogic()
{
}

void GameLogic::SetRenderer(TextRenderer * newRenderer)
{
	if (newRenderer)
	{
		renderer = newRenderer;
		renderer->Initialize();
	}
}

void GameLogic::SetInputHandler(InputHandler * newInput)
{
	if (newInput)
	{
		input = newInput;
		input->Initialize();
	}
}

int GameLogic::MainMenu()
{
	return 0;
}

int GameLogic::DictionarySelection()
{
	return 0;
}

int GameLogic::MainGame()
{
	int ret = 0;
	for (int i = 0; i < 1600; ++i)
	{
		renderer->DrawAllWords();
		renderer->MoveAllWords(ToRight, 1);
		if (i % 25 == 0)
		{
			std::string word = "word" + std::to_string(rand() % 999);
			words.AddWord(word);
			renderer->AddWord(word);
		}
		if (i > 200)
		{
			if (i % 28 == 1)
			{
				if (words.GetWordCount() > 0)
				{
					size_t idx = rand() % (words.GetWordCount() / 3);
					renderer->RemoveWordAtIdx(idx);
					words.RemoveWordAtIdx(idx);
				}
			}
		}
		input->ReadKey();
	}
	return ret;
}

int GameLogic::GameLoop()
{
	return 0;
}