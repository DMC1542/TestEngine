#pragma once
#include "Game.h"

class GameState
{
public:
	Game* game = NULL;
	Vector2i mousePosWindow, mousePosScreen;
	Vector2i res;

	virtual void handleInput() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

	virtual void updateMousePositions() = 0;
};