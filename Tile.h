#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Tile {
public: 
	double noiseVal;
	Sprite sprite;
	int x, y;

	Tile();
	Tile(int x, int y, double noise);
};