#include "ActionSelection.h"
#include "GameplayState.h"

ActionSelection::ActionSelection(GameplayState* parent) {
	this->parent = parent;

	// Initialize the Menu box
	Vector2i currTile = parent->currentTile;
	actionMenu = ActionMenu((currTile.x + 1) * parent->TILE_SIZE, currTile.y * parent->TILE_SIZE);

	// Populate actions
	for (Entity entity )
}

void ActionSelection::handleInput(sf::Time deltaTime) {
	Event event;

	// Allow for normal movement
	parent->applyWASDmovement(deltaTime);

	while (parent->game->window.pollEvent(event)) {
		if (event.type == Event::MouseButtonReleased) {
			if (event.mouseButton.button == Mouse::Left)
			for (Button* button : actionMenu.actionButtons) {
				button->checkForClick();
			}
		}
	}
}

void ActionSelection::draw() {
	actionMenu.draw(parent->game->window);
}

void ActionSelection::update() {
	actionMenu.update(parent->mousePosWindow);
}