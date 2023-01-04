#include "Tile.h"

Tile::Tile()
{
	this->x = -1, this->y = -1;
	animator.numFrames = 2;
	animator.fps = 2;
	animator.frame = IntRect(0, 0, 64, 64);
	noiseVal = 0;
}

Tile::Tile(int x, int y, double noise, int numFrames)
{
	this->x = x;
	this->y = y;
	this->noiseVal = noise;
	animator.numFrames = numFrames;
	animator.fps = 2;
	animator.frame = IntRect(0, 0, 64, 64);
}

void Tile::setTerrain(Terrain terrain, Texture texture)
{
	this->terrain = terrain;
	sprite.setTexture(texture);
}

void Tile::update(Time deltaTime)
{
	lastTimeUpdated += deltaTime.asSeconds();

	if (lastTimeUpdated >= (animator.fps / animator.numFrames))
	{

	}
}
