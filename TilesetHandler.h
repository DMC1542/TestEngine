#pragma once

#include <SFML/Graphics.hpp>
#include <stdio.h>

using namespace sf;

class TilesetHandler
{
public:
	// This might not be the final form!
	Texture grassText, sandText, waterText, rockText;
	Texture grassTileSet;
	Texture animationTEST;
	Texture settlerTroopTexture, settlementTexture;

	Sprite grassSandBR, grassSandTR, grassSandTL, grassSandBL,
		grassSandT, grassSandR, grassSandB, grassSandL;
	Sprite sand;

	TilesetHandler();
	void loadGrass();
};