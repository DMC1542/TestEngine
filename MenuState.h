#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "Button.h"

class MenuState : public GameState
{

public: 
	Sprite sprite;
	Texture texture;
	Button* startButton;
	Button* optionsButton;
	Vector2i currentRes;

	const float BUTTON_WIDTH_SCALE = .1, BUTTON_HEIGHT_SCALE = .1;

	MenuState(Game* g);
	~MenuState();

	void draw();
	void handleInput();
	void update();

	void updateMousePositions();
};