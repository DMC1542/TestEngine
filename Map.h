#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "ResourceManager.h"
#include "Terrain.h"
#include "Noise.h"
#include "EntityBuilder.h"

using namespace std;

class Map
{
public:
	ResourceManager<Texture>* rManager;
	
	int width, pixelWidth;
	int height, pixelHeight;
	vector<vector<Tile>> board;

	// Note to self. Map.entities is a redundant list that enables me to easily iterate over all existing
	// entities, without having to iterate through all tiles on the map.
	vector<Entity*> entities;
	EntityBuilder entityBuilder;
	GameplayState* gameplayState;

	Map();
	Map(int width, int height);

	void generateMap(int64_t seed, int octaves, double scale, double persistence, double lacunarity);
	Sprite getEntitySpriteAt(int i);
	double invLerp(double min, double max, double value);
	void setResourceManager(ResourceManager<Texture>* rManager);
	void provideGameplayContext(GameplayState* gameplayState);
	
	void createEntity(EntityType type, string name, int x, int y, GameplayState* gameplayState);
	void deleteEntity(int id);

private: 
	void checkBorderPlacement(Tile* primaryTile, Tile* secondaryTile, ResourceManager<Texture>* rManager);
};