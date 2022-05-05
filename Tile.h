#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Terrain.h"

using namespace sf;

class Tile {
public: 
	double noiseVal;
	Sprite sprite;
	int x, y;
	Animation animator;
	Terrain terrain;

	Tile();
	Tile(int x, int y, double noise, int numFrames = 1);

	void update(Time deltaTime);

private:
	Int64 lastTimeUpdated = 0;
};