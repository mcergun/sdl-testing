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
	void KeyEnter();
	void KeyBackspace();
	void KeyVisual(char c);
	void ExitRequested();
private:
	TextRenderer *renderer;
	InputHandler *input;
	WordList words;
	std::mutex listMutex;
	bool gameRunning = true;
};

class EventRouter
{
public:
	static void SetGameLogicPtr(GameLogic * ptr);
	static void WordMovedOut(size_t idx);
	static void WordTyped(size_t idx);
	static void KeyEnter();
	static void KeyBackspace();
	static void KeyVisual(char c);
	static void ExitRequested();
	static GameLogic *gameLogic;
};

#endif