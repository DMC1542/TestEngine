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
	Vector2f mouseGameworldCoords, viewLoc, lastMovementVector;

	// Debug variables
	sf::Text mouseTileText, fpsText;
	int mouseTileLocX, mouseTileLocY;
	Font debugFont;
	int actualFPS = 0;

	int viewWidth, viewHeight;
	double zoom;
	bool debugMode = false;
	int const MAX_VELOCITY = 20, ACCELERATION = 10;
	float viewVelocity = 0, decelVelocity = 0;
};