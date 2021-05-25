#pragma once

#include "GameState.h"
#include "Map.h"
#include "ProcGen.h"
#include "TextureHandler.h"

class GameplayState : public GameState
{
public:
	GameplayState(Game* g);
	void draw();
	void handleInput();
	void update();
	void updateMousePositions();

private: 
	Map map;
	TextureHandler tHandler;
	Clock clock;
	//Vector/linked list of entities?
	// Bruh, linked list of entities. Lmao

};