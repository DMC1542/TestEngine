#pragma once
#include <SFML/Graphics.hpp>
#include "Actionable.hpp"
#include "ResourceManager.h"
#include <iostream>

using namespace sf;

enum BUTTON_STATE { BTN_IDLE = 0, BTN_HOVER = 1, BTN_PRESSED = 2 };

class Button
{
public:
	short buttonState;
	Font font;
	Color idleColor, hoverColor, pressedColor;
	RectangleShape shape;
	Texture buttonFaceTexture, buttonPressedTexture;
	Sprite buttonFaceSprite, buttonPressedSprite;
	static const float DEFAULT_WIDTH_RATIO, DEFAULT_HEIGHT_RATIO;

	Button(int x, int y, int width, int height, std::string text);

	void update(Vector2i mousePos);
	void draw(RenderWindow& window);
	bool checkForClick();
	Vector2f getLocation();
	void setAction(std::string action);
	void setActionTarget(Actionable* actionable);

private:
	static ResourceManager<Font> fontManager;

	Text text;
	std::string actionString;
	Actionable* actionable = nullptr;

	void findProperSize();
};