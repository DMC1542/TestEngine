#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
public:

	IntRect frame;
	Sprite sprite;
	int numFrames;
	int fps;
	float timeElapsed;
	
	Animation();
	Animation(Texture* tex, int x, int y, int fps, int numFrames);
	void update(Time deltaTime);

private:
	int currFrame;
	void advance();
};

