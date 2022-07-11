#include "ActionSelection.h"
#include "GameplayState.h"

ActionSelection::ActionSelection(GameplayState* parent) {
	this->parent = parent;

	Vector2i currTile = parent->currentTile;
	actionMenu = ActionMenu((currTile.x + 1) * parent->TILE_SIZE, currTile.y * parent->TILE_SIZE);
}

void ActionSelection::handleInput(sf::Time deltaTime) {
	Event event;

	// Allow for normal movement
	parent->applyWASDmovement(deltaTime);

	while (parent->game->window.pollEvent(event)) {
		if ()
	}
}

void ActionSelection::draw() {
	actionMenu.draw(parent->game->window);
}

void ActionSelection::update() {
	actionMenu.update(parent->mousePosWindow);
}