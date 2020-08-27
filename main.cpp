#include "Game.h"
#include "MenuState.h"

using namespace sf;

int main()
{
	Game game;

	game.pushState(new MenuState(&game));

	game.run();

	return 0;
}