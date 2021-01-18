#pragma once

#include <stack>
#include <SFML/Graphics.hpp>
#include "SettingsHandler.h"

using namespace sf;

class GameState;

class Game
{

public:
	RenderWindow window;
	SettingsHandler sHandler;
	Vector2i currentRes;
	View view;

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