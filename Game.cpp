#include "Game.h"
#include "GameState.h"
#include <iostream>

using namespace sf;

Game::Game()
{
	//Eventually will instantiate to the resolution specified in a config file
	//Figure out how to do fullscreen windowed / borderless fullscreen
	window.create(VideoMode(1920, 1080), "Game", Style::Fullscreen);
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