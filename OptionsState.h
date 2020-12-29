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
	Button* saveButton;
	TextElement mapSizeXField;
	TextElement* focusedTextElement;
	Clock clock;
	Vector2i currentRes, lastAcceptedRes;
	std::map<std::string, TextElement*> elementMap;
	const int BUTTON_WIDTH = 250, BUTTON_HEIGHT = 100;

	// Labels
	Text mapLabel, gameLabel, successfulSaveText;
	Font font;

	bool textFocused = false, saveSuccessful = false, clickHandled = false;
	std::vector<VideoMode> modes;

	OptionsState(Game* g);
	~OptionsState();

	void draw();
	void handleInput();
	void update();

private:
	void setupTextElements();
	void updateMousePositions();
	void checkResolutions();
};