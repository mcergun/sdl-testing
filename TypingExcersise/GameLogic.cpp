#include "GameLogic.h"

GameLogic *EventRouter::gameLogic = nullptr;

void GameLogic::SetRenderer(TextRenderer * newRenderer)
{
	if (newRenderer)
	{
		renderer = newRenderer;
		renderer->SetWordOutNotifier(EventRouter::WordMovedOut);
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

void GameLogic::WordMovedOut(size_t idx)
{
#ifdef _DEBUG
	std::cout << "Removed word is " << words.words[idx] << std::endl;
#endif
	words.RemoveWordAtIdx(idx);
	renderer->RemoveWordAtIdx(idx);
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
	bool gameRunning = true;
	size_t i = 0;
	while (gameRunning)
	{
		renderer->DrawAllWords();
		renderer->MoveAllWords(ToRight, 1);
		i++;
		if (i % 25 == 0)
		{
			std::string word = "word" + std::to_string(rand() % 999);
			words.AddWord(word);
			renderer->AddWord(word);
		}
		if (i > 200)
		{
			if (i % 32 == 1)
			{
				if (words.GetWordCount() > 0)
				{
					size_t idx = rand() % (words.GetWordCount() / 2);
					renderer->RemoveWordAtIdx(idx);
					words.RemoveWordAtIdx(idx);
				}
			}
		}
		input->ReadKey();
	}
	return ret;
}

GameLogic::GameLogic()
{
	EventRouter::SetGameLogicPtr(this);
}


GameLogic::~GameLogic()
{
}

int GameLogic::GameLoop()
{
	return 0;
}

void EventRouter::SetGameLogicPtr(GameLogic * ptr)
{
	gameLogic = ptr;
}

void EventRouter::WordMovedOut(size_t idx)
{
	gameLogic->WordMovedOut(idx);
}
