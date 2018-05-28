#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <mutex>
#include <TextRenderer.h>
#include <InputHandler.h>
#include <WordList.h>

#ifdef _DEBUG
#include <iostream>
#endif

enum GameState
{
	StateMainMenu,
	StateDictionarySelection,
	StateMainGame,
};

struct MenuState
{
	int selectedIdx;

	void IncrementIdx(int by = 1);
	void DecrementIdx(int by = 1);
};

class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	int MainMenu();
	int DictionarySelection();
	int MainGame();
	int GameLoop();
	void SetRenderer(TextRenderer *newRenderer);
	void SetInputHandler(InputHandler *newInput);
	void WordMovedOut(size_t idx);
	void WordTyped(size_t idx);
	void EnterKeyPressed();
	void BackspaceKeyPressed();
	void ArrowKeyPressed(ArrowKey arrow);
	void VisualKeyPressed(char c);
	void PauseRequested();
	void ExitRequested();
private:
	TextRenderer *renderer;
	InputHandler *input;
	WordList words;
	std::mutex listMutex;
	GameState state = StateMainMenu;
	MenuState menu;
	bool gameRunning = true;
};

class EventRouter
{
public:
	static void SetGameLogicPtr(GameLogic * ptr);
	static void WordMovedOut(size_t idx);
	static void WordTyped(size_t idx);
	static void EnterKeyPressed();
	static void BackspaceKeyPressed();
	static void ArrowKeyPressed(ArrowKey arrow);
	static void VisualKeyPressed(char c);
	static void PauseRequested();
	static void ExitRequested();
	static GameLogic *gameLogic;
};

#endif