#include "OptionsState.h"
#include <iostream>

using namespace sf;

OptionsState::OptionsState(Game* g)
{
	game = g;

	backgroundTexture.loadFromFile("graphics/OptionsMenu/naturePixelated.png");
	backgroundSprite.setTexture(backgroundTexture);

	exitButton = new Button(1200, 500, 250, 100, "Exit");

	mapSizeXField.location = Vector2f(500, 100);

	focusedTextElement = &mapSizeXField;
	textFocused = false;
}

OptionsState::~OptionsState()
{
	delete &exitButton;
}

void OptionsState::handleInput()
{
	Event event;

	while (game->window.pollEvent(event))
	{
		if (event.type == Event::MouseButtonReleased)
		{
			//We have a mouse click. Let's see if that triggers our buttons
			updateMousePositions();

			//While we're at it, unless other set, presume text is not highlighted.
			textFocused = false;

			//In case there was a previously selected field, reset color
			focusedTextElement->text.setFillColor(Color::White);

			if (exitButton->checkForClick())
			{
				//This is where I will code the button behavior.

				std::cout << "Exit Button Pressed" << std::endl;
				std::cout << "Exiting options menu." << std::endl;

				game->popState();
				break;
			}
			else if (mapSizeXField.checkForClick(mousePosWindow))
			{
				textFocused = true;
				focusedTextElement = &mapSizeXField;

				//Set the color to blue to indicate focus.
				focusedTextElement->text.setFillColor(Color::Blue);
			}
		}
		//else if (event.type == Event::KeyPressed && event.key.code != Keyboard::BackSpace) 
		
		else if (event.type == sf::Event::TextEntered)
		{
			std::cout << "Key unicode: " << event.text.unicode << std::endl;
			if (textFocused)
			{
				if (event.text.unicode == 27 || event.text.unicode == 13)
				{
					//Escape key or Enter key pressed.
					textFocused = false;

					//Reset color
					focusedTextElement->text.setFillColor(Color::White);
				}
				else if (event.text.unicode == 8)
				{
					//Handles the backspace.
					focusedTextElement->removeLetter();
				}
				else
				{
					focusedTextElement->addLetter(event.text.unicode);
				}
			}
		}
	}
}

void OptionsState::update()
{
	updateMousePositions();
	exitButton->update(mousePosWindow);
	mapSizeXField.update();
}

void OptionsState::draw()
{
	game->window.draw(backgroundSprite);
	exitButton->draw(game->window);

	//Drawing Textfields
	game->window.draw(mapSizeXField.text);
}

void OptionsState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mousePosWindow = Mouse::getPosition();
}