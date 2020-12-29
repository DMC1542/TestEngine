#include "MenuState.h"
#include "OptionsState.h"
#include <iostream>

using namespace sf;

MenuState::MenuState(Game* g)
{
	game = g;

	VideoMode mode = VideoMode::getDesktopMode();
	currentRes = Vector2i(mode.width, mode.height);
	
	//Test
	texture.loadFromFile("graphics/MainMenu/testBackground.png");
	sprite.setTexture(texture);

	float scaleX = game->sHandler.settings["resX"] / static_cast<float>(1920);
	float scaleY = game->sHandler.settings["resY"] / static_cast<float>(1080);

	sprite.setScale(Vector2f(scaleX, scaleY));

	startButton = new Button(currentRes.x / 4 - (BUTTON_WIDTH_SCALE / 2), 
		currentRes.y / 2,
		BUTTON_WIDTH_SCALE * currentRes.x, 
		BUTTON_HEIGHT_SCALE * currentRes.y, 
		"Play");
	optionsButton = new Button(3 * (currentRes.x / 4) - (BUTTON_WIDTH_SCALE * currentRes.x * 3 / 2), 
		currentRes.y / 2, 
		BUTTON_WIDTH_SCALE * 3 * currentRes.x, 
		BUTTON_HEIGHT_SCALE * currentRes.y, 
		"Options Menu");
}

MenuState::~MenuState()
{
	delete &startButton;
	delete &optionsButton;
}

void MenuState::handleInput()
{
	Event event;

	while (game->window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				game->window.close();
			}
			else if (event.key.code == Keyboard::O)
			{
				game->pushState(new MenuState(game));
			}
			else if (event.key.code == Keyboard::P)
			{
				game->popState();
				break;
			}
		}
		else if (event.type == Event::MouseButtonReleased)
		{
			//We have a mouse click. Let's see if that triggers our buttons
			updateMousePositions();

			if (startButton->checkForClick())
			{
				//This is where I will code the button behavior.

				std::cout << "Start Button Pressed" << std::endl;
				std::cout << "Pretending to start the game." << std::endl;

				game->popState();
				//game->pushState(new GameState(&game));

				break;
			}
			if (optionsButton->checkForClick())
			{
				//optionsButton selected. Loading options menu

				std::cout << "Options Button Pressed" << std::endl;
				std::cout << "Pretending to load options menu." << std::endl;

				game->pushState(new OptionsState(game));

				break;
			}
		}
	}
}

void MenuState::draw()
{
	game->window.draw(sprite);
	startButton->draw(game->window);
	optionsButton->draw(game->window);
}

void MenuState::update()
{
	updateMousePositions();

	startButton->update(mousePosWindow);
	optionsButton->update(mousePosWindow);
}

void MenuState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mousePosWindow = Mouse::getPosition();
}