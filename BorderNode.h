#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"

// Constants
int const TILE_SIZE = 64;
const int BORDER_HEIGHT = 3;
const int BORDER_WIDTH = TILE_SIZE;

enum BorderType {
	REGULAR = 0
	// Add more border types here
};

class BorderNode {
public:
	/**
	* Creates a border node for a tile that holds the border type and location data only.
	* All references to the border sprites themselves are shared amongst all objects in
	* global variables.
	* 
	* @pre init() has been called - assets ready for use.
	* 
	* @param borderType An enum that indicates which border style to use. This determines
	*					which global sprite to pull and render.
	*/
	BorderNode(int x, int y, BorderType borderType, ResourceManager<Texture>* rManager, bool isEastOrSouth, bool isVertical = false) {
		this->borderType = borderType;

		switch (borderType) {
			case REGULAR:
				this->sprite = sf::Sprite(rManager->get("graphics/Textures/borders/regularBorder.png"));
				break;
			// Assign more border type 
		}

		int xPos = x * TILE_SIZE, yPos = y * TILE_SIZE;

		if (isEastOrSouth) {
			xPos += TILE_SIZE;
			yPos += TILE_SIZE;
		}

		this->sprite.setOrigin(sf::Vector2f(0, static_cast<int>(BORDER_HEIGHT / 2)));
		this->sprite.setPosition(sf::Vector2f(xPos, yPos));

		if (isVertical) {
			this->sprite.setRotation(90);
		}
	}

	void draw(sf::RenderWindow* target) {
		target->draw(sprite);
	}

private:
	BorderType borderType;
	sf::Sprite sprite;
};
