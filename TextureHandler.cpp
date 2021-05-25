#include "TextureHandler.h"

TextureHandler::TextureHandler()
{
	grassText.loadFromFile("graphics/Textures/grassSheet.png");
	waterText.loadFromFile("graphics/Textures/water.png");
	rockText.loadFromFile("graphics/Textures/mountain.png");
	sandText.loadFromFile("graphics/Textures/basicSand.png");
}