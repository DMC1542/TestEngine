#include "Map.h"
#include "Entity.h"
#include <iostream>
#include "BorderNode.h"

Map::Map()
{
	this->width = -1;
	this->height = -1;
}

Map::Map(int width, int height)
{
	this->width = width;
	this->height = height;
	this->pixelWidth = width * TILE_SIZE;
	this->pixelHeight = height * TILE_SIZE;
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

			currTile.sprite.setPosition(Vector2f(w * TILE_SIZE, h * TILE_SIZE));

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
				board[h][w].setTerrain(Terrain::WATER, tHandler->waterText);
			else if (board[h][w].noiseVal < .35)
				board[h][w].setTerrain(Terrain::SAND, tHandler->sandText);
			else if (board[h][w].noiseVal < .8)
				board[h][w].setTerrain(Terrain::GRASS, tHandler->grassText);
			else
				board[h][w].setTerrain(Terrain::ROCK, tHandler->rockText);
		}
	}

	// Iterate over map (again <sad>) to add BorderNodes
	for (int h = 1; h < height - 1; h++)
	{
		for (int w = 1; w < width - 1; w++)
		{
			Tile currTile = board[h][w];
			Tile neighborTile;

			// Check north
			neighborTile = board[h - 1][w];


			// check south
			neighborTile = board[h + 1][w];

			// check east
			neighborTile = board[h][w + 1];

			// check west
			neighborTile = board[h][w - 1];
		}
	}

	std::cout << "Finished terrain generation" << std::endl;
	return;
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

void Map::createEntity(EntityType type, std::string name, int x, int y, GameplayState* gameplayState)
{
	if (tHandler != NULL)
	{
		Entity* temp = entityBuilder.buildEntity(type, name, x, y, gameplayState);
		std::pair<int, Entity*> entityPair = std::pair<int, Entity*>(temp->id, temp);
		this->board[y][x].entities.insert(entityPair);
		this->entities.push_back(temp);
	}
}

void Map::deleteEntity(int id) {
	// Get the entity from master list, then remove it from the tile
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->id == id) {
			Entity* deletedEntity = (*it);
			entities.erase(it);

			board[deletedEntity->y][deletedEntity->x].entities.erase(deletedEntity->id);
			delete deletedEntity;
			break;
		}
	}
}

void Map::provideGameplayContext(GameplayState* gameplayState) {
	this->gameplayState = gameplayState;
}

// Helpers
void checkBorderPlacement(Tile primaryTile, Tile secondaryTile) {
	bool isVertical = false, isEastOrSouth = false;
	

	// Naive way to place border.
	if (primaryTile.terrain != secondaryTile.terrain) {
		if (primaryTile.x < secondaryTile.x) {			// Is East Tile?
			isVertical = true;
			isEastOrSouth = true;
		} else if (primaryTile.x > secondaryTile.x) {	// Is West Tile?
			isVertical = true;
		}
		else if (primaryTile.y < secondaryTile.y) {		// Is South Tile?
			isEastOrSouth = true;
		}
		
		// Make the node
		BorderNode node(primaryTile.x, primaryTile.y, BorderType::REGULAR, isEastOrSouth, isVertical);

		// Assign the node
		if (primaryTile.x < secondaryTile.x) {			// Is East Tile?
			primaryTile.setEastBorder(&node);
			secondaryTile.setEastBorder(&node);
		}
		else if (primaryTile.x > secondaryTile.x) {		// Is West Tile?
			primaryTile.setWestBorder(&node);
			secondaryTile.setWestBorder(&node);
		}
		else if (primaryTile.y < secondaryTile.y) {		// Is South Tile?
			primaryTile.setSouthBorder(&node);
			secondaryTile.setSouthBorder(&node);
		}
		else {											// North tile
			primaryTile.setNorthBorder(&node);
			secondaryTile.setNorthBorder(&node);
		}
	}
}