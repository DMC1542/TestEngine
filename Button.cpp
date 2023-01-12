#include "Button.h"

const float Button::DEFAULT_WIDTH_RATIO = 0.1f, Button::DEFAULT_HEIGHT_RATIO = 0.1f;

ResourceManager<sf::Font> Button::fontManager;

Button::Button(int x, int y, int width, int height, std::string msg)
{
	sf::Clock clock;
	clock.restart();

	shape.setPosition(Vector2f(x, y));
	shape.setSize(Vector2f(width, height));
	shape.setFillColor(idleColor);

	std::cout << "TIME FOR BUTTON_1: " << clock.getElapsedTime().asSeconds() << std::endl;

	font = fontManager.get("fonts/KOMIKAP_.ttf");

	std::cout << "TIME FOR BUTTON_2: " << clock.getElapsedTime().asSeconds() << std::endl;
	
	// Text size is declared elsewhere.
	text.setString(msg);
	text.setFont(font);
	text.setFillColor(Color::Yellow);

	std::cout << "TIME FOR BUTTON_2.2: " << clock.getElapsedTime().asSeconds() << std::endl;


	findProperSize();

	std::cout << "TIME FOR BUTTON_3: " << clock.getElapsedTime().asSeconds() << std::endl;

	//This centers the text on the shape.
	float weirdOffset = text.getGlobalBounds().top;
	text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - (text.getGlobalBounds().width / 2.f),
		shape.getPosition().y + ((shape.getGlobalBounds().height - text.getGlobalBounds().height) / 2.f) - weirdOffset
	);	

	idleColor = Color::Blue;
	hoverColor = Color::Magenta;
	pressedColor = Color::Green;

	std::cout << "TIME FOR BUTTON_4: " << clock.getElapsedTime().asSeconds() << std::endl;
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
		if (actionable != nullptr) {
			actionable->doAction(actionString);
		}

		return true;
	}
	else {
		return false;
	}
}

Vector2f Button::getLocation()
{
	return shape.getPosition();
}

void Button::findProperSize()
{
	// Set default character size
	text.setCharacterSize(75);

	// Loop until the size is acceptable. 
	float target = shape.getGlobalBounds().width - 20;

	for (int size = 74; text.getGlobalBounds().width >= target; size -= 2)
	{
		text.setCharacterSize(size);
	}
}

void Button::setAction(std::string action) {
	this->actionString = action;
}

void Button::setActionTarget(Actionable* actionable) {
	this->actionable = actionable;
}