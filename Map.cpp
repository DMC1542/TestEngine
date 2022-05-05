#include "Map.h"
#include "Entity.h"
#include <iostream>

Map::Map()
{
	this->width = -1;
	this->height = -1;
}

Map::Map(int width, int height)
{
	this->width = width;
	this->height = height;
}

Map Map::generateMap(int64_t seed, int octaves, double scale, double persistence, double lacunarity)
{
	// Genereate the noise map
	//Map map = ProcGen::generateMap(width, height, seed, octaves, scale, persistence, lacunarity);

	// --------------- Procedural Gen ---------------------------

	std::cout << "Starting procedural map generation" << std::endl;

	Noise::Noise noiseGenerator(seed);
	Map map(width, height);

	double x, y;
	double minNoise = DBL_MAX, maxNoise = DBL_MIN;

	// Ensure that scale is not <= 0
	if (scale <= 0)
		scale = .001;

	for (int height = 0; height < map.height; height++)
	{
		vector<Tile> row;

		for (int width = 0; width < map.width; width++)
		{
			double frequency = 1, amplitude = 1, noiseHeight = 0, noise;

			// Do octaves
			for (int i = 0; i < octaves; i++)
			{
				x = (double)width / scale * frequency;
				y = (double)height / scale * frequency;

				noise = noiseGenerator.eval(x, y); // * 2 - 1, IF it returns values from 0:1 to get -1:1

				// Now using the perlin value, modify amplitude
				noiseHeight += noise * amplitude;

				amplitude *= persistence;
				frequency *= lacunarity;
			}

			if (noiseHeight < minNoise)
				minNoise = noiseHeight;
			if (noiseHeight > maxNoise)
				maxNoise = noiseHeight;


			Tile currTile;
			currTile.x = width;
			currTile.y = height;
			currTile.noiseVal = noiseHeight;

			currTile.sprite.setPosition(Vector2f(width * 64, height * 64));

			row.push_back(currTile);
		}

		map.board.push_back(row);
	}

	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
		{
			map.board[h][w].noiseVal = invLerp(minNoise, maxNoise, map.board[h][w].noiseVal);
		}
	}

	// --------------- End Proc Gen -----------------------------

	// Assign terrains
	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
		{
			Tile currTile = map.board[h][w];

			if (currTile.noiseVal < .3)
			{
				currTile.terrain = WATER;
				map.board[h][w].sprite.setTexture(tHandler.waterText);
			}
			else if (map.board[h][w].noiseVal < .35)
				map.board[h][w].sprite.setTexture(tHandler.sandText);
			else if (map.board[h][w].noiseVal < .8)
			{
				map.board[h][w].sprite.setTexture(tHandler.grassText);
				map.board[h][w].animator.numFrames = 2;
			}
			else
				map.board[h][w].sprite.setTexture(tHandler.rockText);
		}
	}

	// Assign texture edges
	// Not elegant. Mostly for experimentation
	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
		{
			Tile currTile = map.board[h][w];

			// Grass assignment
			if (currTile.terrain == GRASS)
			{
			}
			else if (currTile.terrain == WATER)
				currTile.sprite.setTexture(tHandler.waterText);
			else if (currTile.terrain == SAND)
			{

			}
			else if (currTile.terrain == ROCK)
				currTile.sprite.setTexture(tHandler.rockText);
		}
	}
}

void Map::assignGrassSprite(Map& map, int i, int j)
{
}

void Map::createEntity(string name, int x, int y)
{
	this->entities.push_back(Entity(name, x, y));
}

Sprite Map::getEntitySpriteAt(int i) 
{
	return entities.at(i).animator.sprite;
}

// This normalizes value between the min and max (returns a value between 0 and 1)
double invLerp(double min, double max, double value)
{
	return (value - min) / (max - min);
}