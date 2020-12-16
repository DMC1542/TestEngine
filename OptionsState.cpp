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

	focusedTextElement = elementMap["mapSizeX"];
	textFocused = false;
}

OptionsState::~OptionsState()
{
	std::map<std::string, TextElement*>::iterator it;
	for (it = elementMap.begin(); it != elementMap.end(); it++)
	{
		delete it->second;
	}

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
		
			std::map<std::string, TextElement*>::iterator it;
			for (it = elementMap.begin(); it != elementMap.end(); it++)
			{
				if (it->second->checkForClick(mousePosWindow))
				{
					textFocused = true;
					focusedTextElement = it->second;

					//Set the color to blue to indicate focus.
					focusedTextElement->setFocused(true);
				}
			}
		}		
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

	std::map<std::string, TextElement*>::iterator it;
	for (it = elementMap.begin(); it != elementMap.end(); it++)
	{
		it->second->update();
	}
}

void OptionsState::draw()
{
	game->window.draw(backgroundSprite);
	exitButton->draw(game->window);

	//Drawing Textfields
	std::map<std::string, TextElement*>::iterator it;
	for (it = elementMap.begin(); it != elementMap.end(); it++)
	{
		it->second->draw(game->window);
	}
}

void OptionsState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mousePosWindow = Mouse::getPosition();
}

void OptionsState::setupTextElements()
{
	// Do all text field instantiation here.
	elementMap["mapSizeX"] = new TextElement();
	elementMap["mapSizeY"] = new TextElement();

	elementMap["mapSizeY"]->setLocation(Vector2f(200, 200));
	elementMap["mapSizeY"]->setCharCap(5);
	elementMap["mapSizeY"]->setIntLock(true);
	elementMap["mapSizeY"]->setPrefix("Map Size Y: ");

}
