#include "ActionMenu.h"

const int BUTTON_HEIGHT = 50;

ActionMenu::ActionMenu() {
	this->x = 0;
	this->y = 0;

	menuBox.setPosition(sf::Vector2f(x, y));
	menuBox.setSize(sf::Vector2f(100, BUTTON_HEIGHT));
}

ActionMenu::ActionMenu(int x, int y) {
	// Default size of 10, 10 just to show it exists
	menuBox.setPosition(sf::Vector2f(x, y));
	menuBox.setSize(sf::Vector2f(100, BUTTON_HEIGHT));

	this->x = x;
	this->y = y;
}

void ActionMenu::addItem(std::string actionName, void* (*callback)())
{
	// The width/height are TEMPORARY.
	Button* newButton = &Button(x, y + (actionButtons.size() * BUTTON_HEIGHT),
		200, BUTTON_HEIGHT, actionName);
	actionButtons.push_back(newButton);

	// Update size of the bounding box
	Vector2f newSize = Vector2f(menuBox.getSize().x, menuBox.getSize().y + BUTTON_HEIGHT);
	menuBox.setSize(newSize);
}

void ActionMenu::deleteItems() {
	for (auto it = actionButtons.begin(); it != actionButtons.end(); it++) {
		actionButtons.erase(it);
	}

	menuBox.setSize(Vector2f(0, 0));
}

void ActionMenu::draw(RenderWindow& window) {
	window.draw(menuBox);
	
	for (Button* button : actionButtons) {
		button->draw(window);
	}
}

void ActionMenu::update(Vector2i mousePos) {
	for (Button* button : actionButtons) {
		button->update(mousePos);
	}
}

void ActionMenu::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
	
	menuBox.setPosition(sf::Vector2f(x, y));
}
