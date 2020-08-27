#include "MenuState.h"
#include <iostream>

using namespace sf;

MenuState::MenuState(Game* g)
{
	game = g;
	
	//Test
	texture.loadFromFile("graphics/MainMenu/testBackground.png");
	sprite.setTexture(texture);

	startButton = new Button(500, 500, 250, 100, "Testing text");
}

MenuState::~MenuState()
{
	delete &startButton;
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
			std::cout << startButton->isPressed() << std::endl;
			if (startButton->isPressed())
			{
				//start. testing it by popping state tho
				game->popState();
				break;
			}
		}
	}
}

void MenuState::draw()
{
	game->window.draw(sprite);
	startButton->draw(game->window);
}

void MenuState::update()
{
	updateMousePositions();

	startButton->update(mousePosWindow);
}

void MenuState::updateMousePositions()
{
	mousePosWindow = Mouse::getPosition(game->window);
	mousePosWindow = Mouse::getPosition();
}