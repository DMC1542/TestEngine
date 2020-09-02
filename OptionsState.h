#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"

using namespace sf;

class OptionsState : public GameState
{
public: 
	Texture backgroundTexture;
	Sprite backgroundSprite;
	Button* exitButton;

	OptionsState(Game* g);
	~OptionsState();

	void draw();
	void handleInput();
	void update();

	void updateMousePositions();
};