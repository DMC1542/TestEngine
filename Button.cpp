#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, std::string text)
{
	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));
	shape.setFillColor(idleColor);
	
	/*
	buttonFaceSprite.setPosition(Vector2f(x, y));
	buttonPressedSprite.setPosition(Vector2f(x, y));
	
	buttonFaceTexture.loadFromFile("graphics/MainMenu/TestButtonFace.png");
	buttonPressedTexture.loadFromFile("graphics/MainMenu/TestButtonPressed.png");

	buttonFaceSprite.setTexture(buttonFaceTexture);
	buttonPressedSprite.setTexture(buttonPressedTexture);
	*/

	font.loadFromFile("fonts/KOMIKAP_.ttf");

	this->text.setString(text);
	this->text.setFont(font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(Color::Yellow);
	this->text.setPosition(
		//This centers the text on the shape.
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
	);

	std::cout << (shape.getPosition().x / 2.f) << "-" << (this->text.getGlobalBounds().width / 2.f) << std::endl;
	std::cout << (shape.getPosition().y / 2.f) << "-" << (this->text.getGlobalBounds().height / 2.f) << std::endl;

	idleColor = Color::Blue;
	hoverColor = Color::Magenta;
	pressedColor = Color::Green;
}

void Button::update(Vector2i mousePos)
{
	//Start disabled.
	buttonState = BTN_IDLE;

	if (shape.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y)))
	{
		buttonState = BTN_HOVER;
	}
	
	if (Mouse::isButtonPressed(Mouse::Left) && buttonState == BTN_HOVER)
	{
		buttonState = BTN_PRESSED;
	}

	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		break;

	case BTN_PRESSED:
		shape.setFillColor(pressedColor);
		break;

	default:
		shape.setFillColor(Color::White);
		break;
	}
}

void Button::draw(RenderWindow& window)
{
	/*
	if (buttonState == BTN_PRESSED)
	{
		window.draw(buttonPressedSprite);
	}
	else
	{
		window.draw(buttonFaceSprite);
	}
	*/
	
	window.draw(shape);
	window.draw(text);
}

bool Button::checkForClick()
{
	/*
	This is called when left mouse click is released by a gamestate.
	It will check if the button is currently being pressed. If so, 
	return true and signify that there is an action to be executed.
	*/
	if(buttonState == BTN_PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}