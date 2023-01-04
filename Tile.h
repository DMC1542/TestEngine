#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Animation.h"
#include "Terrain.h"
#include "Entity.h"
#include "BorderNode.h"

using namespace sf;

class Tile {
public: 
	double noiseVal;
	Sprite sprite;
	int x, y;
	Animation animator;
	Terrain terrain;
	//std::vector<Entity*> entities;
	std::map<int, Entity*> entities;

	Tile();
	Tile(int x, int y, double noise, int numFrames = 1);

	void setTerrain(Terrain terrain, Texture texture);
	void update(Time deltaTime);

	// Borders 
	BorderNode* getNorthBorder()	{ return northBorder; }
	BorderNode* getSouthBorder()	{ return southBorder; }
	BorderNode* getEastBorder()		{ return eastBorder; }
	BorderNode* getWestBorder()		{ return westBorder; }

	void setNorthBorder(BorderNode* node)	{ this->northBorder = node; }
	void setSouthBorder(BorderNode* node)	{ this->southBorder = node; }
	void setEastBorder(BorderNode* node)	{ this->eastBorder = node; }
	void setWestBorder(BorderNode* node)	{ this->westBorder = node; }

private:
	Int64 lastTimeUpdated = 0;
	BorderNode *northBorder = nullptr, *southBorder = nullptr, *eastBorder = nullptr, *westBorder = nullptr;

};