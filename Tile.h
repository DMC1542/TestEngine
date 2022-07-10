#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Animation.h"
#include "Terrain.h"
#include "Entity.h"

using namespace sf;

class Tile {
public: 
	double noiseVal;
	Sprite sprite;
	int x, y;
	Animation animator;
	Terrain terrain;
	//std::vector<Entity*> entities;
	std::map<int, Entity*> entities;

	Tile();
	Tile(int x, int y, double noise, int numFrames = 1);

	void update(Time deltaTime);

private:
	Int64 lastTimeUpdated = 0;
};