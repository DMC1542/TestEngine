#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

using namespace sf;

class Tile {
public: 
	double noiseVal;
	Sprite sprite;
	int x, y;
	Animation animator;

	Tile();
	Tile(int x, int y, double noise, int numFrames = 1);
};