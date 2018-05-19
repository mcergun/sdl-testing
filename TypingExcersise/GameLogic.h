#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include <TextRenderer.h>

class GameLogic
{
public:
	GameLogic();
	~GameLogic();
	void SetRenderer(TextRenderer *renderer);
private:
	TextRenderer *renderer;
};

#endif