#include "GameplayState.h"
#include <iostream>

using namespace sf;

GameplayState::GameplayState(Game* g)
{
	game = g;

	// Getting resolution for button placement and image scaling
	res = game->currentRes;

	// My testing lab
	int w = 1920 / 2, h = 1080 / 2, octaves = 4;
	int64_t seed = 1;
	double scale = 5, persistence = .5, lacunarity = 1.2;
	map = ProcGen::generateMap(w, h, seed, octaves, scale, persistence, lacunarity);



	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
		{
			Tile currTile = map.board[h][w];

			if (currTile.noiseVal < .3)
				map.board[h][w].sprite.setTexture(tHandler.waterText);
			else if (map.board[h][w].noiseVal < .35)
				map.board[h][w].sprite.setTexture(tHandler.sandText);
			else if (map.board[h][w].noiseVal < .8)
				map.board[h][w].sprite.setTexture(tHandler.grassText);
			else
				map.board[h][w].sprite.setTexture(tHandler.rockText);
		}
	}
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
			/* draws Noise
			double val = map.noiseValues[h][w] * 255;

			RectangleShape pix(Vector2f(2, 2));
			pix.setPosition(Vector2f(w * 2, h * 2));
			pix.setFillColor(Color(val, val, val, 255));
			game->window.draw(pix);
			*/

			game->window.draw(map.board[h][w].sprite);
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