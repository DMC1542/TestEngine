#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

typedef struct Animation 
{
	IntRect frame;
	int numFrames;
	int fps;
};