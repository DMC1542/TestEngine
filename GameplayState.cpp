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
	int rightView = (int)ceil(game->window.getSize().x / (float)TILE_SIZE);
	int bottomView = (int)ceil(game->window.getSize().y / (float)TILE_SIZE) ;
	viewBounds = { 0, rightView, 0, bottomView };

	// Music
	music.openFromFile("audio/mozart.wav");
	music.play();

	// Debug mode init
	debugFont.loadFromFile("fonts/Montserrat-Regular.ttf");
	mouseTileText.setFont(debugFont);
	mouseTileText.setFillColor(Color::White);
	mouseTileText.setOutlineColor(Color::Black);
	fpsText.setFont(debugFont);
	fpsText.setFillColor(Color::White);
	fpsText.setOutlineColor(Color::Black);
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
		mouseTileLocX = mouseGameworldCoords.x / TILE_SIZE;
		mouseTileLocY = mouseGameworldCoords.y / TILE_SIZE;

		string mouseTileLoc("Tile XY: " + to_string(mouseTileLocX) + ", " + to_string(mouseTileLocY));

		mouseTileText.setString(mouseTileLoc);
		mouseTileText.setPosition(mouseGameworldCoords + Vector2f(0, -20));

		actualFPS = 1 / deltaTime.asSeconds();
		fpsText.setString("FPS: " + to_string(actualFPS));
		fpsText.setPosition((mouseGameworldCoords + Vector2f(0, -45)));
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
		game->window.draw(fpsText);
	}
}

void GameplayState::handleInput()
{
	Event event;
	Time deltaTime = clock.getElapsedTime();

	// Handling movement separately so I can control acceleration of the view
	bool isMoving = false;
	Vector2f movementAmount(0, 0);

	// viewVelo = old velocity * (1 - delta_time * transition_speed) + desired_velocity * (delta_time * transition_speed);
	//viewVelocity = viewVelocity * (1 - deltaTime.asSeconds() * transitionSpeed) + desiredVelocity * (deltaTime.asSeconds() * transitionSpeed);
	

	// This allows for multiple keystrokes at once to movement the view - no longer limited to one movement vector.
	// All keystrokes influence one overall movement vector that is applied at the end of the update cycle.
	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		isMoving = true;
		if (viewVelocity < MAX_VELOCITY)
			viewVelocity += ACCELERATION * deltaTime.asSeconds();

		movementAmount.x += viewVelocity;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		isMoving = true;
		if (viewVelocity < MAX_VELOCITY)
			viewVelocity += ACCELERATION * deltaTime.asSeconds();

		movementAmount.x -= viewVelocity;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		isMoving = true;
		if (viewVelocity < MAX_VELOCITY)
			viewVelocity += ACCELERATION * deltaTime.asSeconds();

		movementAmount.y -= viewVelocity;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		isMoving = true;
		if (viewVelocity < MAX_VELOCITY)
			viewVelocity += ACCELERATION * deltaTime.asSeconds();

		movementAmount.y += viewVelocity;
	}
	
	// Decelerate
	if (!isMoving) {
		viewVelocity -= ACCELERATION * 3 * deltaTime.asSeconds();

		if (viewVelocity > 0)
		{
			if (lastMovementVector.x > 0)
				movementAmount.x += viewVelocity;
			else if (lastMovementVector.x < 0)
				movementAmount.x -= viewVelocity;
			if (lastMovementVector.y > 0)
				movementAmount.y += viewVelocity;
			else if (lastMovementVector.y < 0)
				movementAmount.y -= viewVelocity;
		}
		else
			viewVelocity = 0;
	}

	if (isMoving)
	{
		// Manually update the current view location, apply boundings
		viewLoc += movementAmount;
		if (viewLoc.x <= 0)
			viewLoc.x = 0;
		else if (viewLoc.x > map.pixelWidth)
			viewLoc.x = map.pixelWidth;

		if (viewLoc.y <= 0)
			viewLoc.y = 0;
		else if (viewLoc.y > map.pixelHeight)
			viewLoc.y = map.pixelHeight;
	}

	// Apply bounded movement
	lastMovementVector = movementAmount;
	game->view.move(movementAmount);
	game->window.setView(game->view);


	while (game->window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				music.stop();
				music.~Music();

				game->view.zoom(1);
				game->window.setView(game->view);

				game->view.move(Vector2f(-TILE_SIZE * zoom * viewBounds.left, -TILE_SIZE * zoom * viewBounds.top));
				game->window.setView(game->view);
				game->popState();
				break;				// Critical! Without this break, the loop will continue
									// executing after pop - leading to null ptr exception.
			}
			else if (event.key.code == Keyboard::Equal)
			{
				if (zoom > .25)
				{
					zoom -= .25;
					double scaleFactor = zoom / (zoom + .25);
					game->view.zoom(scaleFactor);
					game->window.setView(game->view);
				}
			}
			else if (event.key.code == Keyboard::Dash)
			{
				if (zoom < 2)
				{
					zoom += .25;

					double scaleFactor = zoom / (zoom - .25);
					game->view.zoom(scaleFactor);
					game->window.setView(game->view);
				}
			}
			else if (event.key.code == Keyboard::F1)
				debugMode = !debugMode;
		}
		else if (event.type == Event::KeyReleased) {
			// ways to detect when we aren't holding a key anymore.
		}
	}
}

void GameplayState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mouseGameworldCoords = game->window.mapPixelToCoords(Mouse::getPosition());
}