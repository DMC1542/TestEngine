#pragma once
#include "Game.h"

class GameState
{
public:
	Game* game = NULL;

	virtual void handleInput() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};