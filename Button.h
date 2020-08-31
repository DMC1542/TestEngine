#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum BUTTON_STATE { BTN_IDLE = 0, BTN_HOVER = 1, BTN_PRESSED = 2 };

class Button
{
public:
	short buttonState;
	Font font;
	Text text;
	Color idleColor, hoverColor, pressedColor;
	RectangleShape shape;
	Texture buttonFaceTexture, buttonPressedTexture;
	Sprite buttonFaceSprite, buttonPressedSprite;


	Button(int x, int y, int width, int height, std::string text);

	void update(Vector2i mousePos);
	void draw(RenderWindow& window);
	bool checkForClick();
};