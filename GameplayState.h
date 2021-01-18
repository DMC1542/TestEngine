#pragma once

#include "GameState.h"

class GameplayState : public GameState
{
public:
	GameplayState(Game* g);
	void draw();
	void handleInput();
	void update();

private: 
	//Map map;
	//Vector/linked list of entities?

};