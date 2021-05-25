#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

using namespace std;

class Map
{
public:
	int width;
	int height;
	vector<vector<Tile>> board;

	Map();
	Map(int width, int height);
};