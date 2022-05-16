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
	map = Map(100, 100);
	map.setTilesetHandler(&tHandler);
	map.generateMap(seed, octaves, scale, persistence, lacunarity);
	//map.createEntity(EntityType::TEST, "Test", 0, 0);
	//map.createEntity(EntityType::TEST, "Test", 1, 1);
	map.createEntity(EntityType::SETTLER, "Player 1 Settler", 2, 2);

	// Defining view width and height
	zoom = 1;

	// Initial view bounds. Gets window's size, gets # of tiles visible + 1 in case of underestimate
	int rightView = (game->window.getSize().x / TILE_SIZE) + 1;
	int bottomView = (game->window.getSize().y / TILE_SIZE) + 1;
	viewBounds = { 0, rightView, 0, bottomView };

	// Music
	music.openFromFile("audio/mozart.wav");
	music.play();

	// Debug mode init
	debugFont.loadFromFile("fonts/Montserrat-Regular.ttf");
	mouseTileText.setFont(debugFont);
	mouseTileText.setFillColor(Color::White);
	mouseTileText.setOutlineColor(Color::Black);
}

void GameplayState::update()
{
	Time deltaTime = clock.restart();
	updateMousePositions();

	for (int h = viewBounds.top; h < viewBounds.bottom; h++)
	{
		for (int w = viewBounds.left; w < viewBounds.right; w++)
		{
			// This may be modified. Animation may only be applied to entities.
			map.board[h][w].update(deltaTime);
		}
	}

	// Update entities
	for (int i = 0; i < map.entities.size(); i++)
	{
		map.entities.at(i)->update(deltaTime);
	}

	// Debug updates
	if (debugMode) {
		mouseTileLocX = (mousePosWindow.x / (TILE_SIZE * zoom)) + viewBounds.left;
		mouseTileLocY = (mousePosWindow.y / (TILE_SIZE * zoom)) + viewBounds.top;
		string mouseTileLoc("Tile XY: " + to_string(mouseTileLocX) + ", " + to_string(mouseTileLocY));

		int gameworldMouseCoordsX = mousePosWindow.x + viewBounds.left * TILE_SIZE;
		int gameworldMouseCoordsY = mousePosWindow.y + viewBounds.top * TILE_SIZE;
		mouseTileText.setString(mouseTileLoc);
		mouseTileText.setPosition(Vector2f(gameworldMouseCoordsX, gameworldMouseCoordsY));
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

	if (debugMode)
	{
		game->window.draw(mouseTileText);
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
				music.stop();
				music.~Music();

				game->view.move(Vector2f(-TILE_SIZE * zoom * viewBounds.left, -TILE_SIZE * zoom * viewBounds.top));
				game->window.setView(game->view);
				game->popState();
				break;				// Critical! Without this break, the loop will continue
									// executing after pop - leading to null ptr exception.
			}
			else if (event.key.code == Keyboard::D)
			{
				if (viewBounds.right < map.width)
				{
					viewBounds.left += 1;
					viewBounds.right += 1;
					game->view.move(Vector2f(TILE_SIZE * zoom, 0));
					game->window.setView(game->view);
				}
			}
			else if (event.key.code == Keyboard::A)
			{
				if (viewBounds.left > 0)
				{
					viewBounds.left -= 1;
					viewBounds.right -= 1;
					game->view.move(Vector2f(-TILE_SIZE * zoom, 0));
					game->window.setView(game->view);
				}
			}
			else if (event.key.code == Keyboard::W)
			{
				if (viewBounds.top > 0)
				{
					viewBounds.top -= 1;
					viewBounds.bottom -= 1;
					game->view.move(Vector2f(0, -TILE_SIZE * zoom));
					game->window.setView(game->view);
				}
			}
			else if (event.key.code == Keyboard::S)
			{
				if (viewBounds.bottom < map.height)
				{
					viewBounds.top += 1;
					viewBounds.bottom += 1;
					game->view.move(Vector2f(0, TILE_SIZE * zoom));
					game->window.setView(game->view);
				}
			}
			else if (event.key.code == Keyboard::L)
				debugMode = !debugMode;
		}
	}
}

void GameplayState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mousePosScreen = Mouse::getPosition();
}