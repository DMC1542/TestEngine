#include "Animation.h"

using namespace sf;

const int TILE_SIZE = 64;

Animation::Animation()
{
	// Placeholder.
	timeElapsed = -1;
}

Animation::Animation(std::string fileName, int x, int y, int fps, int numFrames)
{
	this->frame.left = x;
	this->frame.top = y;
	this->frame.height = TILE_SIZE;
	this->frame.width = TILE_SIZE;

	this->tex.loadFromFile(fileName);
	this->sprite.setTexture(tex);
	this->sprite.setTextureRect(frame);
	this->fps = fps;
	this->numFrames = numFrames;
	this->timeElapsed = 0;
	this->currFrame = 0;
}

void Animation::update(Time deltaTime)
{
	this->timeElapsed += deltaTime.asSeconds();
	advance();

	return;
}

void Animation::advance() 
{
	if (timeElapsed >= 1 / fps)
	{
		// Reduce time to be within [0, 1 / fps)
		while (timeElapsed >= 1 / fps)
			timeElapsed -= 1 / fps;

		currFrame++;

		if (currFrame >= numFrames)
			currFrame = 0;

		frame.left = currFrame * 64;
	}

	return;
}