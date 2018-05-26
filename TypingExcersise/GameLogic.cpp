#include "GameLogic.h"

GameLogic *EventRouter::gameLogic = nullptr;

void GameLogic::SetRenderer(TextRenderer * newRenderer)
{
	if (newRenderer)
	{
		renderer = newRenderer;
		renderer->SetWordOutNotifier(EventRouter::WordMovedOut);
		words.SetWordTypedNotifier(EventRouter::WordTyped);
		renderer->Initialize();
	}
}

void GameLogic::SetInputHandler(InputHandler * newInput)
{
	if (newInput)
	{
		input = newInput;
		input->Initialize();
		input->SetKeyEnterNotifier(EventRouter::KeyEnter);
		input->SetKeyBackspaceNotifier(EventRouter::KeyBackspace);
		input->SetKeyVisualNotifier(EventRouter::KeyVisual);
		input->SetPauseEventNotifier(EventRouter::PauseRequested);
		input->SetExitEventNotifier(EventRouter::ExitRequested);
	}
}

void GameLogic::WordMovedOut(size_t idx)
{
#ifdef _DEBUG
	std::cout << "Removed word is " << words.activeWords[idx] << std::endl;
#endif
	words.RemoveWordAtIdx(idx);
	renderer->RemoveWordAtIdx(idx);
}

void GameLogic::WordTyped(size_t idx)
{
#ifdef _DEBUG
	std::cout << "Typed word is " << words.activeWords[idx] << std::endl;
#endif
	words.RemoveWordAtIdx(idx);
	renderer->RemoveWordAtIdx(idx);
}

void GameLogic::KeyEnter()
{
#ifdef _DEBUG
	std::cout << "Enter Key" << std::endl;
#endif
}

void GameLogic::KeyBackspace()
{
#ifdef _DEBUG
	std::cout << "Backspace Key" << std::endl;
#endif
	words.EraseLastCharacter();
	renderer->UpdateWrittenWord(words.GetCompareBuffer());
}

void GameLogic::KeyVisual(char c)
{
#ifdef _DEBUG
	std::cout << "Key " << c << std::endl;
#endif
	words.DoesCharMatch(c);
	renderer->UpdateWrittenWord(words.GetCompareBuffer());
}

void GameLogic::PauseRequested()
{
	gameRunning = false;
}

void GameLogic::ExitRequested()
{
	gameRunning = false;
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
	size_t i = 0;
	words.ReadFile("google-10000-english-usa.txt");
	while (gameRunning)
	{
		renderer->DrawAllWords();
		renderer->MoveAllWords(ToRight, 1);
		i++;
		if (i % 80 == 0)
		{
			std::string &word = words.GetRandomWord();
			words.AddWord(word);
			renderer->AddWord(word);
		}
		if (i > 200)
		{
			//if (i % 32 == 1)
			//{
			//	if (words.GetWordCount() > 0)
			//	{
			//		size_t idx = rand() % (words.GetWordCount() / 2);
			//		renderer->RemoveWordAtIdx(idx);
			//		words.RemoveWordAtIdx(idx);
			//	}
			//}
		}
		int ret = input->ReadKey();
	}
	renderer->CloseWindow();
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
	switch (state)
	{
	case StateMainMenu:
		break;
	case StateDictionarySelection:
		break;
	case StateMainGame:
		break;
	default:
		break;
	}
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

void EventRouter::WordTyped(size_t idx)
{
	gameLogic->WordTyped(idx);
}

void EventRouter::KeyEnter()
{
}

void EventRouter::KeyBackspace()
{
	gameLogic->KeyBackspace();
}

void EventRouter::KeyVisual(char c)
{
	gameLogic->KeyVisual(c);
}

void EventRouter::PauseRequested()
{
	gameLogic->PauseRequested();
}

void EventRouter::ExitRequested()
{
	gameLogic->ExitRequested();
}
