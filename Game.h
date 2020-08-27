#pragma once

#include <stack>
#include <SFML/Graphics.hpp>

using namespace sf;

class GameState;

class Game
{

public:
	RenderWindow window;

	Game();
	~Game();

	//Main game loop
	void run();

	//State handling methods
	GameState* currentState();
	void pushState(GameState* gs);
	void popState();

private:
	std::stack<GameState*> states;
};