#include "OptionsState.h"
#include <iostream>

using namespace sf;

OptionsState::OptionsState(Game* g)
{
	game = g;

	backgroundTexture.loadFromFile("graphics/OptionsMenu/naturePixelated.png");
	backgroundSprite.setTexture(backgroundTexture);
	
	exitButton = new Button(1200, 500, 250, 100, "Exit");

	setupTextElements();

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
			focusedTextElement->setFocused(false);

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
				focusedTextElement->setFocused(true);
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
					focusedTextElement->setFocused(false);
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
	mapSizeXField.draw(game->window);
}

void OptionsState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mousePosWindow = Mouse::getPosition();
}

void OptionsState::setupTextElements()
{
	//Do all text field instantiation here.
	mapSizeXField.setCharCap(5);
	mapSizeXField.setIntLock(true);
}
