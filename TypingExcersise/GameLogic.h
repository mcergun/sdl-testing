#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

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
private:
	TextRenderer *renderer;
	InputHandler *input;
	WordList words;
};

class EventRouter
{
public:
	static void SetGameLogicPtr(GameLogic * ptr);
	static void WordMovedOut(size_t idx);
	static void WordTyped(size_t idx);
	static GameLogic *gameLogic;
};

#endif