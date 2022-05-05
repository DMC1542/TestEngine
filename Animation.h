#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
public:

	IntRect frame;
	Texture tex;
	Sprite sprite;
	int numFrames;
	int fps;
	Int64 timeElapsed;
	
	Animation();
	Animation(std::string fileName, int x, int y, int fps, int numFrames);
	void update(Time deltaTime);

private:
	int currFrame;
	void advance();
};

