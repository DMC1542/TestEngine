#include "GameplayState.h"
#include <iostream>

using namespace sf;

GameplayState::GameplayState(Game* g)
{
	game = g;

	// Getting resolution for button placement and image scaling
	res = game->currentRes;
	
	// TODO load textures
	// TODO generate map
	Map map = ProcGen::generateMap(10, 10, 1, 4, 20, .5, 1);

	
	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
			printf("%4.4f ", map.noiseValues[h][w]);

		std::cout << std::endl;
	}

	cout << map.noiseValues[1][1] << endl;
}

void GameplayState::update()
{

}

void GameplayState::draw()
{

}

void GameplayState::handleInput()
{
	Event event;

	while (game->window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				game->popState();
			}
		}
	}
}

void GameplayState::updateMousePositions()
{
	// stuff!
}