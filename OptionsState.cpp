#include "OptionsState.h"
#include <iostream>
#include <fstream>

using namespace sf;

OptionsState::OptionsState(Game* g)
{
	game = g;

	backgroundTexture.loadFromFile("graphics/OptionsMenu/naturePixelated.png");
	backgroundSprite.setTexture(backgroundTexture);

	font.loadFromFile("fonts/KOMIKAP_.ttf");


	// Preparing locations for buttons
	VideoMode mode = VideoMode::getDesktopMode();
	currentRes = Vector2i(mode.width, mode.height);
	Vector2f exitButtonLoc = Vector2f(mode.width / 2, mode.height - BUTTON_HEIGHT);
	Vector2f saveButtonLoc = Vector2f(mode.width / 2 - BUTTON_WIDTH, mode.height - BUTTON_HEIGHT);

	// Set up buttons
	exitButton = new Button(exitButtonLoc.x, exitButtonLoc.y, BUTTON_WIDTH, BUTTON_HEIGHT, "Exit");
	saveButton = new Button(saveButtonLoc.x, saveButtonLoc.y, BUTTON_WIDTH, BUTTON_HEIGHT, "Save");

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
				checkResolutions();

				clickHandled = true;

				// Applying settings configuration
				// See if the resolution changed, and if so, change the screen res
				if (elementMap["resX"]->getText() !=
					std::to_string(game->sHandler.settings["resX"])
					|| elementMap["resY"]->getText() !=
					std::to_string(game->sHandler.settings["resY"]))
				{
					int resX, resY;
					resX = std::stoi(elementMap["resX"]->getText());
					resY = std::stoi(elementMap["resY"]->getText());

					game->window.create(VideoMode(resX, resY), "Game", Style::Fullscreen);
				}

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
				checkResolutions();
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
					checkResolutions();
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
	mousePosWindow = Mouse::getPosition();
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
	elementMap["resX"] = new TextElement("Resolution Width: ", 4, true);
	elementMap["resY"] = new TextElement("Resolution Height: ", 4, true);
	elementMap["fullscreen"] = new TextElement("Fullscreen: ", 1, true);

	elementMap["mapSizeX"]->setLocation(Vector2f(0, 100));
	elementMap["mapSizeY"]->setLocation(Vector2f(0, 150));
	elementMap["resX"]->setLocation(Vector2f(450, 100));
	elementMap["resY"]->setLocation(Vector2f(450, 150));
	elementMap["fullscreen"]->setLocation(Vector2f(450, 200));

	lastAcceptedRes = Vector2i(game->sHandler.settings["mapSizeX"],
		game->sHandler.settings["mapSizeY"]);
	elementMap["mapSizeX"]->setBodyText(std::to_string(game->sHandler.settings["mapSizeX"]));
	elementMap["mapSizeY"]->setBodyText(std::to_string(game->sHandler.settings["mapSizeY"]));
	elementMap["resX"]->setBodyText(std::to_string(game->sHandler.settings["resX"]));
	elementMap["resY"]->setBodyText(std::to_string(game->sHandler.settings["resY"]));
	elementMap["fullscreen"]->setBodyText(std::to_string(game->sHandler.settings["fullscreen"]));
}

void OptionsState::checkResolutions()
{
	int resX = std::stoi(elementMap["resX"]->getText());
	int resY = std::stoi(elementMap["resY"]->getText());

	for (int i = 0; i < modes.size(); i++)
	{
		if (elementMap["resX"]->isCurrentlyFocused())
		{
			if (resX == modes.at(i).width)
			{
				//It is legal, change the other coord.
				elementMap["resY"]->setBodyText(std::to_string(modes.at(i).height));
				lastAcceptedRes = Vector2i(stoi(elementMap["resX"]->getText()), 
					stoi(elementMap["resY"]->getText()));
				return;
			}
		}
		else if (elementMap["resY"]->isCurrentlyFocused())
		{
			if (resY == modes.at(i).height)
			{
				//It is legal, change the other coord.
				elementMap["resX"]->setBodyText(std::to_string(modes.at(i).width));
				lastAcceptedRes = Vector2i(stoi(elementMap["resX"]->getText()),
					stoi(elementMap["resY"]->getText()));
				return;
			}
		}
	}

	// Otherwise,
	elementMap["resX"]->setBodyText(std::to_string(lastAcceptedRes.x));
	elementMap["resY"]->setBodyText(std::to_string(lastAcceptedRes.y));
}