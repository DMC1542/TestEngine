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
	std::map<std::string, TextElement*> elementMap;

	bool textFocused;

	OptionsState(Game* g);
	~OptionsState();

	void draw();
	void handleInput();
	void update();

private:
	void setupTextElements();
	void updateMousePositions();
};