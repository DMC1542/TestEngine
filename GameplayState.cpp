#include "GameplayState.h"
#include "FeatureState.h"
#include "TestFeature.h"
#include "ActionSelection.h"
#include "BorderNode.h"

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
	map.provideGameplayContext(this);
	map.setResourceManager(&rManager);
	map.generateMap(seed, octaves, scale, persistence, lacunarity);
	map.createEntity(EntityType::SETTLER, "Player 1 Settler", 2, 2, this);

	// Defining view width and height
	zoom = 1;
	viewLimit.x = TILE_SIZE * map.width;
	viewLimit.y = TILE_SIZE * map.height;
	originalCenter = game->view.getCenter();

	// Initial view bounds. Gets window's size, gets # of tiles visible + 1 in case of underestimate
	int rightView = (int)ceil(game->window.getSize().x / (double)TILE_SIZE) + 1;
	int bottomView = (int)ceil(game->window.getSize().y / (double)TILE_SIZE) + 1;
	viewBounds = { 0, rightView, 0, bottomView };

	// Music
	music.openFromFile("audio/mozart.wav");
	//music.play();

	// Selected tile init
	selectedTile.setOutlineColor(Color::Black);
	selectedTile.setOutlineThickness(3);
	selectedTile.setFillColor(Color::Transparent);
	selectedTile.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
}

void GameplayState::update()
{
	Time deltaTime = clock.restart();
	updateMousePositions();

	if (!featureStates.empty()) {
		featureStates.top()->update();
	} else {
		// Update current tile
		currentTile.x = mouseGameworldCoords.x / TILE_SIZE;
		currentTile.y = mouseGameworldCoords.y / TILE_SIZE;
		selectedTile.setPosition(Vector2f(currentTile.x * TILE_SIZE, currentTile.y * TILE_SIZE));

		// Update all tiles
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
			// TEMPORARY
			fpsText.setString("LR, TB: " + to_string(viewBounds.left) + ", " + to_string(viewBounds.right) +
				", " + to_string(viewBounds.top) + ", " + to_string(viewBounds.bottom));
			fpsText.setPosition((mouseGameworldCoords + Vector2f(0, -45)));
		} 
	}
}

void GameplayState::draw()
{
	// Print the board
	for (int h = viewBounds.top; h < viewBounds.bottom; h++)
	{
		for (int w = viewBounds.left; w < viewBounds.right; w++)
		{
			game->window.draw(map.board[h][w].getSprite());
		}
	}

	// Draw borders here
	for (int h = viewBounds.top; h < viewBounds.bottom; h++)
	{
		for (int w = viewBounds.left; w < viewBounds.right; w++)
		{
			if (map.board[h][w].getNorthBorder() != nullptr) {
				game->window.draw(map.board[h][w].getNorthBorder()->getSprite());
			}

			if (map.board[h][w].getEastBorder() != nullptr) {
				game->window.draw(map.board[h][w].getEastBorder()->getSprite());
			}

			if (map.board[h][w].getWestBorder() != nullptr) {
				game->window.draw(map.board[h][w].getWestBorder()->getSprite());
			}

			if (map.board[h][w].getSouthBorder() != nullptr) {
				game->window.draw(map.board[h][w].getSouthBorder()->getSprite());
			}
		}
	}

	// Display entities
	for (int i = 0; i < map.entities.size(); i++)
	{
		game->window.draw(map.getEntitySpriteAt(i));
	}

	// Draw selected tile
	game->window.draw(selectedTile);

	if (debugMode)
	{
		game->window.draw(mouseTileText);
		game->window.draw(fpsText);
	}

	// If feature states, draw their visuals
	if (!featureStates.empty())
		featureStates.top()->draw();
}

void GameplayState::handleInput()
{
	// We want to enable features to hijack control schemes.
	// However, there's an option available to maintain regular controls.

	/* if COMPLETE_CONTROL
	 *		Pass the event straight to the feature state for handling.
	 *		All queued events become consumed. (Just trap control flow here)
	 * if SELECTIVE_CONTROL
	 *		
	 */

	Event event;
	Time deltaTime = clock.getElapsedTime();

	// If there's a feature state, use its bindings first
	if (!featureStates.empty())
	{
		featureStates.top()->handleInput(deltaTime);
	}
	else {
		// We have no feature states. Handle all controls normally.
		// First, allow movement
		applyWASDmovement(deltaTime);

		// Handle non-key related events
		while (game->window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				/* This is the only key - related event that must be outside the applyNormalKeybinds()
				* method because it directly influences the control flow of the event queue polling loop.
				* All other key press events can be removed into the normal keybind method.
				*/
				if (event.key.code == Keyboard::Escape)
				{
					music.stop();
					music.~Music();

					game->view.zoom(1);	// TODO fix this. 1 keeps view the same.
					game->window.setView(game->view);

					game->view.move(Vector2f(-TILE_SIZE * zoom * viewBounds.left, -TILE_SIZE * zoom * viewBounds.top));
					game->window.setView(game->view);
					game->popState();
					break;				// Critical! Without this break, the loop will continue
										// executing after pop - leading to null ptr exception.
				}
				else {
					applyNormalKeybinds(event.key.code);
				}
			}
			else if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					featureStates.push(new ActionSelection(this));
				}
			}
			else if (event.type == Event::Closed) {
				// Catches window closure, can elegantly close the application here. 
			}
		}
	}
}

void GameplayState::updateMousePositions() {
	mousePosWindow = Mouse::getPosition(game->window);
	mouseGameworldCoords = game->window.mapPixelToCoords(Mouse::getPosition());
}

void GameplayState::applyNormalKeybinds(Keyboard::Key key) {
	if (key == Keyboard::Equal)
	{
		if (zoom > .25)
		{
			zoom -= .25;

			double scaleFactor = zoom / (zoom + .25);
			game->view.zoom(scaleFactor);
			game->window.setView(game->view);
		}
	}
	else if (key == Keyboard::Dash)
	{
		if (zoom < 2)
		{
			zoom += .25;

			double scaleFactor = zoom / (zoom - .25);
			game->view.zoom(scaleFactor);
			game->window.setView(game->view);

			correctViewBounds();
		}
	}
	else if (key == Keyboard::F1)
		debugMode = !debugMode;
	else if (key == Keyboard::P) { /* My Debugging key */
		SettlerTroop* test = static_cast<SettlerTroop*>((getTile(2, 2)->getEntities()->begin())->second);
		test->placeSettlement();
	}
}

void GameplayState::applyWASDmovement(Time deltaTime) {
	// Handling movement separately so I can control acceleration of the view
	bool isMoving = false;
	movementAmount = Vector2f(0, 0);

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

	// Manually update the current view location, apply boundings
	correctViewBounds();

	// Apply bounded movement
	lastMovementVector = movementAmount;
	game->view.move(movementAmount);
	game->window.setView(game->view);

	// Figure out the new render window
	calcViewBounds();
}

void GameplayState::calcViewBounds() {
	Vector2f center = game->view.getCenter();
	viewBounds.left = (center.x - (game->view.getSize().x / 2)) / TILE_SIZE;
	viewBounds.right = (center.x + (game->view.getSize().x / 2)) / TILE_SIZE + 1;
	viewBounds.top = (center.y - (game->view.getSize().y / 2)) / TILE_SIZE;
	viewBounds.bottom = (center.y + (game->view.getSize().y / 2)) / TILE_SIZE + 1;

	if (viewBounds.right > map.width)
		viewBounds.right = map.width;
	if (viewBounds.bottom > map.height)
		viewBounds.bottom = map.height;
}

void GameplayState::correctViewBounds() {

	// just use the outer boxes, not the center.
	Vector2f currentCenter = game->view.getCenter();
	double widthOffset = floor(game->view.getSize().x / 2) - 1;  // the - 1 is to prevent the screen from getting stuck outside bounds from floating point errors.
	double heightOffset = floor(game->view.getSize().y / 2) - 1;

	if (currentCenter.x - widthOffset < 0) {
		game->view.setCenter(Vector2f(widthOffset, currentCenter.y));
		movementAmount.x = 0;
		viewVelocity = 0;
	}
	else if (currentCenter.x + widthOffset > viewLimit.x) {
		game->view.setCenter(Vector2f(viewLimit.x - widthOffset, currentCenter.y));
		movementAmount.x = 0;
		viewVelocity = 0;
	}

	if (currentCenter.y - heightOffset < 0) {
		game->view.setCenter(Vector2f(currentCenter.x, heightOffset));
		movementAmount.y = 0;
		viewVelocity = 0;
	} else if (currentCenter.y + heightOffset > viewLimit.y) {
		game->view.setCenter(Vector2f(currentCenter.x, viewLimit.y - heightOffset));
		movementAmount.y = 0;
		viewVelocity = 0;
	}
}

void GameplayState::initDebugMode() {
	// Debug mode init
	debugFont.loadFromFile("fonts/Montserrat-Regular.ttf");
	mouseTileText.setFont(debugFont);
	mouseTileText.setFillColor(Color::White);
	mouseTileText.setOutlineColor(Color::Black);
	fpsText.setFont(debugFont);
	fpsText.setFillColor(Color::White);
	fpsText.setOutlineColor(Color::Black);
}

Tile* GameplayState::getTile(int x, int y) {
	return &map.board[y][x];
}

void GameplayState::createEntity(EntityType type, std::string name, int x, int y) {
	map.createEntity(type, name, x, y, this);
}

void GameplayState::deleteEntity(int id) {
	map.deleteEntity(id);
}