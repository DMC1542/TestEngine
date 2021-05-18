#include "GameplayState.h"

using namespace sf;

GameplayState::GameplayState(Game* g)
{
	game = g;

	// Getting resolution for button placement and image scaling
	res = game->currentRes;
	
	// TODO load textures
	// TODO generate map
}

void GameplayState::update()
{

}

void GameplayState::draw()
{

}

void GameplayState::handleInput()
{

}