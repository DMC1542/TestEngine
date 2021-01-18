#include "Game.h"
#include "GameState.h"
#include <iostream>

using namespace sf;

Game::Game()
{
	//Eventually will instantiate to the resolution specified in a config file
	//Figure out how to do fullscreen windowed / borderless fullscreen
	sHandler.getSettings();
	VideoMode mode = VideoMode::getDesktopMode();
	int resX = mode.width;
	int resY = mode.height;
	currentRes = Vector2i(resX, resY);

	Image icon;
	icon.loadFromFile("graphics/MainMenu/testIcon.png");

	view.setCenter(resX / 2, resY / 2);
	view.setSize(resX, resY);

	window.create(VideoMode(resX, resY), "Game", Style::Fullscreen);
	window.setIcon(132, 114, icon.getPixelsPtr());
	window.setFramerateLimit(60);
	window.setView(view);
}

Game::~Game()
{
	while (!states.empty())
	{
		popState();
	}
}

//Game related functions
void Game::run()
{
	while (window.isOpen())
	{
		currentState()->handleInput();

		//Checking if there is a state present, if the user popped states.
		if (currentState() == nullptr)
		{
			std::cout << "No states in stack. Terminating the game." << std::endl;
			break;
		}

		currentState()->update();

		// Drawing the screen ----------------------
		window.clear();

		currentState()->draw();

		window.display();
	}
}

//Gamestate functions

GameState* Game::currentState()
{
	if (!states.empty())
	{
		return states.top();
	}
	else
	{
		std::cout << "currentState() called on empty stack. Returned nullptr." << std::endl;
		return nullptr;
	}
}

void Game::pushState(GameState* gs)
{
	states.push(gs);
}

void Game::popState()
{
	if (!states.empty())
	{
		delete states.top();
		states.pop();
	}
	else
	{
		std::cout << "Tried popping state when empty. Aborting." << std::endl;
	}
}