#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TilesetHandler.h"
#include "Terrain.h"
#include "Entity.h"
#include "Noise.h"

using namespace std;

class Map
{
private:
	TilesetHandler* tHandler;
	void assignGrassSprite(Map &map, int i, int j);

public:
	int width;
	int height;
	vector<vector<Tile>> board;
	vector<Entity> entities;

	Map();
	Map(int width, int height);
	void generateMap(int64_t seed, int octaves, double scale, double persistence, double lacunarity);
	Sprite getEntitySpriteAt(int i);
	void createEntity(string name, Texture* tex, int x, int y);
	double invLerp(double min, double max, double value);
	void setTilesetHandler(TilesetHandler* tHandler);
};