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

void Map::generateMap(int64_t seed, int octaves, double scale, double persistence, double lacunarity)
{
	// Genereate the noise map
	// --------------- Procedural Gen ---------------------------

	std::cout << "Starting procedural map generation" << std::endl;

	Noise::Noise noiseGenerator(seed);

	double x, y;
	double minNoise = DBL_MAX, maxNoise = DBL_MIN;

	// Ensure that scale is not <= 0
	if (scale <= 0)
		scale = .001;

	for (int h = 0; h < height; h++)
	{
		vector<Tile> row;

		for (int w = 0; w < width; w++)
		{
			double frequency = 1, amplitude = 1, noiseHeight = 0, noise;

			// Do octaves
			for (int i = 0; i < octaves; i++)
			{
				x = (double)w / scale * frequency;
				y = (double)h / scale * frequency;

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
			currTile.x = w;
			currTile.y = h;
			currTile.noiseVal = noiseHeight;

			currTile.sprite.setPosition(Vector2f(w * 64, h * 64));

			row.push_back(currTile);
		}

		board.push_back(row);
	}

	std::cout << "Normalizing noise values" << std::endl;

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			board[h][w].noiseVal = invLerp(minNoise, maxNoise, board[h][w].noiseVal);
		}
	}

	// --------------- End Proc Gen -----------------------------

	std::cout << "Assigning terrain types" << std::endl;

	// Assign terrains
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			Tile currTile = board[h][w];

			if (currTile.noiseVal < .3)
				board[h][w].sprite.setTexture(tHandler->waterText);
			else if (board[h][w].noiseVal < .35)
				board[h][w].sprite.setTexture(tHandler->sandText);
			else if (board[h][w].noiseVal < .8)
				board[h][w].sprite.setTexture(tHandler->grassText);
			else
				board[h][w].sprite.setTexture(tHandler->rockText);
		}
	}

	std::cout << "Finished terrain generation" << std::endl;
	return;
}


void Map::createEntity(EntityType type, std::string name, int x, int y)
{
	if (tHandler != NULL)
	{
		Entity* temp = entityBuilder.buildEntity(type, name, x, y);
		this->board[y][x].entities.push_back(temp);
		this->entities.push_back(temp);
	}
}

Sprite Map::getEntitySpriteAt(int i) 
{
	return entities.at(i)->getSprite();
}

// This normalizes value between the min and max (returns a value between 0 and 1)
double Map::invLerp(double min, double max, double value)
{
	return (value - min) / (max - min);
}

void Map::setTilesetHandler(TilesetHandler* tHandler)
{
	this->tHandler = tHandler;
	this->entityBuilder = EntityBuilder(tHandler);
}