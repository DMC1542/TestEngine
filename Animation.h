#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

typedef struct Animation
{
	IntRect frame;
	Texture tex;
	int numFrames;
	int fps;
};