#include "Tile.h"

Tile::Tile()
{
	int x = -1, y = -1;
}

Tile::Tile(int x, int y, double noise)
{
	this->x = x;
	this->y = y;
	this->noiseVal = noise;
}
