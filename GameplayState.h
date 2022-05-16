#pragma once

#include "GameState.h"
#include "Map.h"
#include "TilesetHandler.h"
#include <SFML/Audio/Music.hpp>

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
	Music music;
	
	// Debug variables
	sf::Text mouseTileText;
	int mouseTileLocX, mouseTileLocY;
	Font debugFont;

	int viewWidth, viewHeight;
	double zoom;
	bool debugMode = false;
	//Vector/linked list of entities?
	// Bruh, linked list of entities. Lmao
};