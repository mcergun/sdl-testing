#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <TextRenderer.h>
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
	void SetRenderer(TextRenderer *renderer);
private:
	TextRenderer *renderer;
	WordList words;
};

#endif