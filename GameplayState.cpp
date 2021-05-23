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

	// My testing lab
	int w = 1920 / 2, h = 1080 / 2, octaves = 4;
	int64_t seed = 1;
	double scale = 5, persistence = .5, lacunarity = 1.2;
	map = ProcGen::generateMap(w, h, seed, octaves, scale, persistence, lacunarity);

	/*
	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
			printf("%4.4f ", map.noiseValues[h][w]);

		std::cout << std::endl;
	}
	*/
}

void GameplayState::update()
{

}

void GameplayState::draw()
{
	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
		{
			double val = map.noiseValues[h][w] * 255;

			RectangleShape pix(Vector2f(2, 2));
			pix.setPosition(Vector2f(w * 2, h * 2));
			pix.setFillColor(Color(val, val, val, 255));
			game->window.draw(pix);
		}
	}
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