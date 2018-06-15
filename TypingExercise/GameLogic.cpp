#include "GameLogic.h"

GameLogic *EventRouter::gameLogic = nullptr;

void MenuState::IncrementIdx(int by)
{
	if (by + selectedIdx >= 0 && by + selectedIdx < 3)
		selectedIdx += by;
}

void MenuState::DecrementIdx(int by)
{
	if (by - selectedIdx >= 0 && by - selectedIdx < 3)
		selectedIdx -= by;
}

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
		input->SetEnterKeyNotifier(EventRouter::EnterKeyPressed);
		input->SetBackspaceKeyNotifier(EventRouter::BackspaceKeyPressed);
		input->SetArrowKeyNotifier(EventRouter::ArrowKeyPressed);
		input->SetVisualKeyNotifier(EventRouter::VisualKeyPressed);
		input->SetPauseEventNotifier(EventRouter::PauseRequested);
		input->SetExitEventNotifier(EventRouter::ExitRequested);
	}
}

void GameLogic::WordMovedOut(size_t idx)
{
	size_t wordLen = words.activeWords[idx].length();
	if (wordLen < 4)
	{
		gameScore -= (wordLen * 1.5);
	}
	else if (wordLen < 8)
	{
		gameScore -= wordLen;
	}
	else
	{
		gameScore -= (wordLen * 0.5);
	}
	renderer->UpdateScore(gameScore);
#ifdef _DEBUG
	std::cout << "Removed word is " << words.activeWords[idx] <<
		", Score = " << gameScore << std::endl;
#endif
	words.RemoveWordAtIdx(idx);
	renderer->RemoveWordAtIdx(idx);
}

void GameLogic::WordTyped(size_t idx)
{
	size_t wordLen = words.activeWords[idx].length();
	if (wordLen < 4)
	{
		gameScore += (wordLen * 0.5);
	}
	else if (wordLen < 8)
	{
		gameScore += wordLen;
	}
	else
	{
		gameScore += (wordLen * 1.5);
	}
	renderer->UpdateScore(gameScore);
#ifdef _DEBUG
	std::cout << "Typed word is " << words.activeWords[idx] <<
		", Score = " << gameScore << std::endl;
#endif
	words.RemoveWordAtIdx(idx);
	renderer->RemoveWordAtIdx(idx);
}

void GameLogic::EnterKeyPressed()
{
#ifdef _DEBUG
	std::cout << "Enter Key" << std::endl;
#endif
	switch (state)
	{
	case StateMainMenu:
		renderer->Reset();
		state = StateMainGame;
		break;
	case StateDictionarySelection:
		break;
	case StateMainGame:
		break;
	default:
		break;
	}
}

void GameLogic::BackspaceKeyPressed()
{
#ifdef _DEBUG
	std::cout << "Backspace Key" << std::endl;
#endif
	words.EraseLastCharacter();
	renderer->UpdateWrittenWord("=>  " + words.GetCompareBuffer());
}

void GameLogic::ArrowKeyPressed(ArrowKey arrow)
{
	switch (state)
	{
	case StateMainMenu:
		switch (arrow)
		{
		case ArrowUp:
			//menu.DecrementIdx();
			//renderer->RemoveWordAtIdx(menu.selectedIdx);
			//renderer->AddWordAt("Changed", 100, (menu.selectedIdx + 1) * 50, ColorYellow);
			break;
		case ArrowDown:
			//menu.IncrementIdx();
			//renderer->RemoveWordAtIdx(menu.selectedIdx);
			//renderer->AddWordAt("Changed", 100, (menu.selectedIdx + 1) * 50, ColorYellow);
			break;
		case ArrowRight:
			break;
		case ArrowLeft:
			break;
		default:
			break;
		}
		break;
	case StateDictionarySelection:
		break;
	case StateMainGame:
		break;
	default:
		break;
	}
}

void GameLogic::VisualKeyPressed(char c)
{
#ifdef _DEBUG
	std::cout << "Key " << c << std::endl;
#endif
	words.DoesCharMatch(c);
	renderer->UpdateWrittenWord("=>  " + words.GetCompareBuffer());
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
	int ret = 0;
	static int menuState = 0;
	switch (menuState)
	{
	case 0:
		renderer->AddWordAt("Totally placeholder", 100, 50, ColorWhite);
		renderer->AddWordAt("Start", 100, 100, ColorCyan);
		renderer->AddWordAt("Options", 100, 150, ColorYellow);
		renderer->AddWordAt("Select Dictionary", 100, 200, ColorMagenta);
		renderer->AddWordAt("Exit", 100, 250, ColorGray);
		menuState = 1;
		break;
	case 1:
		ret = renderer->DrawAllWords();
		ret |= input->ReadKey();
	default:
		break;
	}
	return 0;
}

int GameLogic::DictionarySelection()
{
	return 0;
}

int GameLogic::MainGame()
{
	static int ret = 0;
	static size_t i = 0;
	renderer->DrawAllWords();
	renderer->MoveAllWords(ToRight, 1);
	i++;
	if (i % 80 == 0)
	{
		std::string &word = words.GetRandomWord();
		words.AddWord(word);
		renderer->AddWord(word);
	}
	ret = input->ReadKey();
	return ret;
}

GameLogic::GameLogic()
{
	EventRouter::SetGameLogicPtr(this);
	srand(time(NULL));
}


GameLogic::~GameLogic()
{
}

int GameLogic::GameLoop()
{
	words.ReadFile("google-10000-english-usa.txt");
	while (gameRunning)
	{
		switch (state)
		{
		case StateMainMenu:
			MainMenu();
			break;
		case StateDictionarySelection:
			break;
		case StateMainGame:
			MainGame();
			break;
		default:
			break;
		}
	}
	renderer->CloseWindow();
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

void EventRouter::EnterKeyPressed()
{
	gameLogic->EnterKeyPressed();
}

void EventRouter::BackspaceKeyPressed()
{
	gameLogic->BackspaceKeyPressed();
}

void EventRouter::ArrowKeyPressed(ArrowKey arrow)
{
	gameLogic->ArrowKeyPressed(arrow);
}

void EventRouter::VisualKeyPressed(char c)
{
	gameLogic->VisualKeyPressed(c);
}

void EventRouter::PauseRequested()
{
	gameLogic->PauseRequested();
}

void EventRouter::ExitRequested()
{
	gameLogic->ExitRequested();
}
