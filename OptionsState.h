#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#include "TextElement.h"

using namespace sf;

class OptionsState : public GameState
{
public: 
	Texture backgroundTexture;
	Sprite backgroundSprite;
	Button* exitButton;
	TextElement mapSizeXField;
	TextElement* focusedTextElement;

	bool textFocused;

	OptionsState(Game* g);
	~OptionsState();

	void draw();
	void handleInput();
	void update();

	void updateMousePositions();
	void setupTextElements();

private:
	void initializeElements();
};