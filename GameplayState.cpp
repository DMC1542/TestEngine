#include "GameplayState.h"
#include <iostream>

using namespace sf;

GameplayState::GameplayState(Game* g)
{
	game = g;

	// Getting resolution for button placement and image scaling
	res = game->currentRes;

	// My testing lab
	int resWidth = 1920 / 2, resHeight = 1080 / 2, octaves = 4;
	int64_t seed = 1;
	double scale = 5, persistence = .5, lacunarity = 1.2;
	//map = ProcGen::generateMap(resWidth, resHeight, seed, octaves, scale, persistence, lacunarity);
	map = Map(100, 100);
	map.generateMap(seed, octaves, scale, persistence, lacunarity);
	map.createEntity("Test", 0, 0);

	// Defining view width and height
	zoom = 1;

	// Initial view bounds. Gets window's size, gets # of tiles visible + 1 in case of underestimate
	int rightView = (game->window.getSize().x / TILE_SIZE) + 1; 
	int bottomView = (game->window.getSize().y / TILE_SIZE) + 1;
	viewBounds = { 0, rightView, 0, bottomView};
}

void GameplayState::update()
{
	for (int h = viewBounds.top; h < viewBounds.bottom; h++)
	{
		for (int w = viewBounds.left; w < viewBounds.right; w++)
		{
			// This may be modified. Animation may only be applied to entities.
			map.board[h][w].update(clock.getElapsedTime());
		}
	}

	// Update entities
	for (int i = 0; i < map.entities.size(); i++)
	{
		map.entities.at(i).update(clock.getElapsedTime());
	}
}

void GameplayState::draw()
{
	// Print the board
	for (int h = viewBounds.top; h < viewBounds.bottom; h++)
	{
		for (int w = viewBounds.left; w < viewBounds.right; w++)
		{
			game->window.draw(map.board[h][w].sprite);
		}
	}

	// Display entities
	for (int i = 0; i < map.entities.size(); i++)
	{
		game->window.draw(map.getEntitySpriteAt(i));
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
				break;
			}
		}
	}
}

void GameplayState::updateMousePositions()
{
	// stuff!
}