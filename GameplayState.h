#pragma once

#include "GameState.h"
#include "Map.h"
#include "ResourceManager.h"
#include <SFML/Audio/Music.hpp>

// Forward declaration. Tells compiler this will be defined, just externally.
class FeatureState;
class ActionSelection;
class Entity;

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

	ResourceManager<Texture> rManager;
	std::stack<FeatureState*> featureStates;
	Vector2i currentTile;
	
	void applyWASDmovement(Time deltaTime);
	void applyNormalKeybinds(Keyboard::Key key);
	Tile* getTile(int x, int y);
	void createEntity(EntityType type, std::string name, int x, int y);
	void deleteEntity(int id);

private:
	Map map;
	Clock clock;
	ViewBounds viewBounds;
	Music music;
	Vector2f mouseGameworldCoords, lastMovementVector;
	RectangleShape selectedTile;

	// Debug variables
	sf::Text mouseTileText, fpsText;
	int mouseTileLocX, mouseTileLocY;
	Font debugFont;
	int actualFPS = 0;
	Vector2f originalCenter, viewLimit;

	double zoom;
	bool debugMode = false;
	int const MAX_VELOCITY = 20, ACCELERATION = 10;
	double viewVelocity = 0, decelVelocity = 0;
	Vector2f movementAmount;

	void calcViewBounds();
	void correctViewBounds();
	void initDebugMode();
};