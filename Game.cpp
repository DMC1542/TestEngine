#include "Game.h"
#include "GameState.h"
#include <iostream>

using namespace sf;

Game::Game()
{
	//Eventually will instantiate to the resolution specified in a config file
	//Figure out how to do fullscreen windowed / borderless fullscreen
	sHandler.getSettings();
	int resX = sHandler.settings["resX"];
	int resY = sHandler.settings["resY"];

	window.create(VideoMode(resX, resY), "Game", Style::Fullscreen);
	
	std::vector<VideoMode> modes = VideoMode::getFullscreenModes();
	std::cout << resX << " " << resY << std::endl;
	for (int i = 0; i < modes.size(); i++)
	{
		std::cout << modes[i].width << ", " << modes[i].height << std::endl;
	}
	
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
	Clock clock;
	clock.restart();

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

		Time time = clock.getElapsedTime();
		//std::cout << "Game FPS: " << 1 / time.asSeconds() << std::endl;
		clock.restart();
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