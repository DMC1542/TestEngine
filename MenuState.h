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

	MenuState(Game* g);
	~MenuState();

	void draw();
	void handleInput();
	void update();

	void updateMousePositions();
};