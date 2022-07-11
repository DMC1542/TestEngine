#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class ActionMenu {
public:
	ActionMenu();
	ActionMenu(int x, int y);
	void addItem(std::string actionName, void* (*callback)());
	void deleteItems();
	void draw(RenderWindow& window);
	void update(Vector2i mousePos);
	void setPosition(int x, int y);
	
	// Returns void*, the (*) means it's a function pointer, () means no args
	std::vector<Button*> actionButtons;

private:
	sf::RectangleShape menuBox;
	int x, y;
};