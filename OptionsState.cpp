#include "OptionsState.h"
#include <iostream>
#include <fstream>

using namespace sf;

OptionsState::OptionsState(Game* g)
{
	game = g;
	
	// Getting resolution for button placement and image scaling
	res = game->currentRes;

	// Setting up background image
	backgroundTexture.loadFromFile("graphics/OptionsMenu/naturePixelated.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(Vector2f(res.x / backgroundSprite.getGlobalBounds().width,
		res.y / backgroundSprite.getGlobalBounds().height));

	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Preparing locations for buttons
	Vector2f saveButtonLoc = Vector2f(res.x / 2 - ((float)res.x * Button::DEFAULT_WIDTH_RATIO),
		res.y - (res.y * Button::DEFAULT_HEIGHT_RATIO));
	Vector2f exitButtonLoc = Vector2f(res.x / 2,
		res.y - (res.y * Button::DEFAULT_HEIGHT_RATIO));

	// Set up buttons
	float buttonWidth = res.x * Button::DEFAULT_WIDTH_RATIO;
	float buttonHeight = res.y * Button::DEFAULT_HEIGHT_RATIO;

	exitButton = new Button(exitButtonLoc.x, exitButtonLoc.y, buttonWidth, buttonHeight, "Exit");
	saveButton = new Button(saveButtonLoc.x, saveButtonLoc.y, buttonWidth, buttonHeight, "Save");

	setupTextElements();

	focusedTextElement = elementMap["mapSizeX"];

	modes = VideoMode::getFullscreenModes();
}

OptionsState::~OptionsState()
{
	std::map<std::string, TextElement*>::iterator it;
	for (it = elementMap.begin(); it != elementMap.end(); it++)
	{
		delete it->second;
	}

	delete &exitButton;
	delete &saveButton;
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

			if (exitButton->checkForClick())
			{
				//This is where I will code the button behavior.
				clickHandled = true;

				std::cout << "Exit Button Pressed" << std::endl;
				std::cout << "Exiting options menu." << std::endl;
				
				game->popState();
				break;
			}
			else if (saveButton->checkForClick())
			{
				clickHandled = true;

				// Applying settings configuration
				std::cout << "Saving current settings configuration." << std::endl;

				std::ofstream outputFile;
				outputFile.open("config.ini");

				std::map<std::string, TextElement*>::iterator it;
				for (it = elementMap.begin(); it != elementMap.end(); it++)
				{
					outputFile << it->first << ":" << it->second->getText() << std::endl;
				}

				outputFile.close();

				saveSuccessful = true;
				clock.restart();
			}
			else
			{
				std::map<std::string, TextElement*>::iterator it;
				for (it = elementMap.begin(); it != elementMap.end(); it++)
				{
					if (it->second->checkForClick(mousePosWindow))
					{
						// First disable the textelement in focus
						focusedTextElement->setFocused(false);

						textFocused = true;
						focusedTextElement = it->second;

						//Set the color to blue to indicate focus.
						focusedTextElement->setFocused(true);

						clickHandled = true;
					}
				}
			}

			if (!clickHandled)
			{
				//In case there was a previously selected field, reset color
				focusedTextElement->setFocused(false);
			}

			clickHandled = false;
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
	saveButton->update(mousePosWindow);

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
	saveButton->draw(game->window);

	//Drawing Textfields
	std::map<std::string, TextElement*>::iterator it;
	for (it = elementMap.begin(); it != elementMap.end(); it++)
	{
		it->second->draw(game->window);
	}

	game->window.draw(mapLabel);
	game->window.draw(gameLabel);


	// Draw save successful if appropriate
	if (saveSuccessful)
	{
		if (clock.getElapsedTime().asSeconds() <= 3)
		{
			game->window.draw(successfulSaveText);
		}
		else
			saveSuccessful = false;
	}
}

void OptionsState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
}

void OptionsState::setupTextElements()
{
	mapLabel.setFont(font);
	mapLabel.setString("Map Settings");
	mapLabel.setPosition(Vector2f(100, 50));
	mapLabel.setFillColor(Color::Black);

	gameLabel.setFont(font);
	gameLabel.setString("Game Settings");
	gameLabel.setPosition(Vector2f(500, 50));
	gameLabel.setFillColor(Color::Black);

	Vector2f loc = saveButton->getLocation();
	successfulSaveText.setFont(font);
	successfulSaveText.setString("Settings successfully saved.");
	successfulSaveText.setPosition(Vector2f(loc.x, loc.y - 40));
	successfulSaveText.setFillColor(Color::Green);

	// Do all text field instantiation here.
	elementMap["mapSizeX"] = new TextElement("Map Size X: ", 5, true);
	elementMap["mapSizeY"] = new TextElement("Map Size Y: ", 5, true);
	elementMap["fullscreen"] = new TextElement("Fullscreen: ", 1, true);

	elementMap["mapSizeX"]->setLocation(Vector2f(0, 100));
	elementMap["mapSizeY"]->setLocation(Vector2f(0, 150));
	elementMap["fullscreen"]->setLocation(Vector2f(450, 200));

	elementMap["mapSizeX"]->setBodyText(std::to_string(game->sHandler.settings["mapSizeX"]));
	elementMap["mapSizeY"]->setBodyText(std::to_string(game->sHandler.settings["mapSizeY"]));
	elementMap["fullscreen"]->setBodyText(std::to_string(game->sHandler.settings["fullscreen"]));
}