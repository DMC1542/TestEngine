#include "TilesetHandler.h"

TilesetHandler::TilesetHandler()
{
	grassText.loadFromFile("graphics/Textures/grassSheet.png");
	waterText.loadFromFile("graphics/Textures/water.png");
	rockText.loadFromFile("graphics/Textures/mountain.png");
	sandText.loadFromFile("graphics/Textures/basicSand.png");
	animationTEST.loadFromFile("graphics/animationTest.png");
	settlerTroopTexture.loadFromFile("graphics/Entities/settlerTroop.png");
	settlementTexture.loadFromFile("graphics/Entities/settlement.png");
}

void TilesetHandler::loadGrass()
{
	grassTileSet.loadFromFile("graphics/tileSet.png");
	//I don't like this
	// B = Bottom, R = Right, T = Top, L = Left. 
	grassSandBR.setTextureRect(sf::IntRect(0, 0, 64, 64));
	grassSandB.setTextureRect(sf::IntRect(64, 0, 64, 64));
	grassSandBL.setTextureRect(sf::IntRect(128, 0, 64, 64));
	grassSandR.setTextureRect(sf::IntRect(0, 64, 64, 64));
	grassSandL.setTextureRect(sf::IntRect(128, 64, 64, 64));
	grassSandTR.setTextureRect(sf::IntRect(0, 128, 64, 64));
	grassSandT.setTextureRect(sf::IntRect(64, 128, 64, 64));
	grassSandTL.setTextureRect(sf::IntRect(128, 128, 64, 64));
	sand.setTextureRect(sf::IntRect(64, 64, 64, 64));

}