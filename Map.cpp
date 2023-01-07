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

			currTile.getSprite().setPosition(Vector2f(w * TILE_SIZE, h * TILE_SIZE));

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
			Tile* currTile = &board[h][w];

			if (currTile->noiseVal < .3)
				currTile->setTerrain(Terrain::WATER, rManager->get("graphics/Textures/water.png"));
			else if (currTile->noiseVal < .35)
				currTile->setTerrain(Terrain::SAND, rManager->get("graphics/Textures/basicSand.png"));
			else if (currTile->noiseVal < .8)
				currTile->setTerrain(Terrain::GRASS, rManager->get("graphics/Textures/grassSheet.png"));
			else
				currTile->setTerrain(Terrain::ROCK, rManager->get("graphics/Textures/mountain.png"));
		}
	}

	// Iterate over map (again <sad>) to add BorderNodes
	for (int h = 1; h < height - 1; h++)
	{
		for (int w = 1; w < width - 1; w++)
		{
			Tile* currTile = &board[h][w];
			Tile* neighborTile;

			// Check north
			neighborTile = &board[h - 1][w];
			checkBorderPlacement(currTile, neighborTile, rManager);

			// check south
			neighborTile = &board[h + 1][w];
			checkBorderPlacement(currTile, neighborTile, rManager);

			// check east
			neighborTile = &board[h][w + 1];
			checkBorderPlacement(currTile, neighborTile, rManager);

			// check west
			neighborTile = &board[h][w - 1];
			checkBorderPlacement(currTile, neighborTile, rManager);
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

void Map::setResourceManager(ResourceManager<Texture>* rManager)
{
	this->rManager = rManager;
	this->entityBuilder = EntityBuilder(rManager);
}

void Map::createEntity(EntityType type, std::string name, int x, int y, GameplayState* gameplayState)
{
	if (rManager != NULL)
	{
		Entity* temp = entityBuilder.buildEntity(type, name, x, y, gameplayState);
		std::pair<int, Entity*> entityPair = std::pair<int, Entity*>(temp->id, temp);
		this->board[y][x].getEntities()->insert(entityPair);
		this->entities.push_back(temp);
	}
}

void Map::deleteEntity(int id) {
	// Get the entity from master list, then remove it from the tile
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if ((*it)->id == id) {
			Entity* deletedEntity = (*it);

			board[deletedEntity->y][deletedEntity->x].getEntities()->erase(deletedEntity->id);
			this->entities.erase(it);
			delete deletedEntity;
			break;
		}
	}
}

void Map::provideGameplayContext(GameplayState* gameplayState) {
	this->gameplayState = gameplayState;
}

// Helpers
void Map::checkBorderPlacement(Tile* primaryTile, Tile* secondaryTile, ResourceManager<Texture>* rManager) {
	bool isVertical = false, isEastOrSouth = false;

	// Naive way to place border.
	if (primaryTile->terrain != secondaryTile->terrain) {
		if (primaryTile->x < secondaryTile->x) {			// Is East Tile?
			isVertical = true;
			isEastOrSouth = true;
		} else if (primaryTile->x > secondaryTile->x) {	// Is West Tile?
			isVertical = true;
		}
		else if (primaryTile->y < secondaryTile->y) {		// Is South Tile?
			isEastOrSouth = true;
		}
		
		// Make the node
		BorderNode* node = new BorderNode(primaryTile->x, primaryTile->y, BorderType::REGULAR, rManager, isEastOrSouth, isVertical);

		// Assign the node
		if (primaryTile->x < secondaryTile->x && primaryTile->getEastBorder() == nullptr) {			// Is East Tile?
			primaryTile->setEastBorder(node);
			secondaryTile->setWestBorder(node);
		}
		else if (primaryTile->x > secondaryTile->x && primaryTile->getWestBorder() == nullptr) {		// Is West Tile?
			primaryTile->setWestBorder(node);
			secondaryTile->setEastBorder(node);
		}
		else if (primaryTile->y < secondaryTile->y && primaryTile->getSouthBorder() == nullptr) {		// Is South Tile?
			primaryTile->setSouthBorder(node);
			secondaryTile->setNorthBorder(node);
		}
		else if (primaryTile->getNorthBorder() == nullptr) {											// North tile
			primaryTile->setNorthBorder(node);
			secondaryTile->setSouthBorder(node);
		}
	}
}