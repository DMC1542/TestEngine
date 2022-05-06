#pragma once

#include "GameState.h"
#include "Map.h"
#include "TilesetHandler.h"

typedef struct ViewBounds
{
	int left;
	int right;
	int top;
	int bottom;
};

class GameplayState : public GameState
{
public:
	GameplayState(Game* g);
	void draw();
	void handleInput();
	void update();
	void updateMousePositions();
	const int TILE_SIZE = 64;

	TilesetHandler tHandler;

private:
	Map map;
	Clock clock;
	ViewBounds viewBounds;

	int viewWidth, viewHeight;
	double zoom;
	//Vector/linked list of entities?
	// Bruh, linked list of entities. Lmao

};