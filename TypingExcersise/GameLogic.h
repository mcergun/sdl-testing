#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <TextRenderer.h>
#include <InputHandler.h>
#include <WordList.h>

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
private:
	TextRenderer *renderer;
	InputHandler *input;
	WordList words;
};

#endif