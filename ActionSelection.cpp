#include "ActionSelection.h"
#include "GameplayState.h"

ActionSelection::ActionSelection(GameplayState* parent) {
	this->parent = parent;

	// Initialize the Menu box
	Vector2i currTile = parent->currentTile;
	auto entities = parent->getTile(currTile.x, currTile.y)->getEntities();
	actionMenu = ActionMenu((currTile.x + 1) * parent->TILE_SIZE, currTile.y * parent->TILE_SIZE);

	// Populate actions
	for (auto it = entities->begin(); it != entities->end(); it++) {
		std::vector<std::string> actions = it->second->actions;
		

		if (actions.size() != 0) {
			for (int i = 0; i < actions.size(); i++) {
				actionMenu.addItem(actions.at(i), it->second);
			}
		}
	}
}

void ActionSelection::handleInput(sf::Time deltaTime) {
	Event event;

	// Allow for normal movement
	parent->applyWASDmovement(deltaTime);

	while (parent->game->window.pollEvent(event)) {
		if (event.type == Event::MouseButtonReleased) {
			if (event.mouseButton.button == Mouse::Left)
			{
				bool clicked = false;

				for (Button* button : actionMenu.actionButtons) {
					clicked = button->checkForClick();
				}

				if (clicked) {
					destroy();
					break;
				}
			}
		}
		else if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Escape) {
				destroy();
				break;
			}
			else
				parent->applyNormalKeybinds(event.key.code);
		}
	}
}

void ActionSelection::draw() {
	actionMenu.draw(parent->game->window);
}

void ActionSelection::update() {
	actionMenu.update(parent->mousePosWindow);
}

void ActionSelection::destroy() {
	actionMenu.deleteItems();
	parent->featureStates.pop();
}