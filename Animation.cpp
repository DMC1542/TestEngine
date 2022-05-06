#include "Animation.h"

using namespace sf;

const int TILE_SIZE = 64;

Animation::Animation()
{
	// Placeholder.
	timeElapsed = -1;
}

Animation::Animation(Texture* tex, int x, int y, int fps, int numFrames)
{
	this->frame = IntRect(x, y, TILE_SIZE, TILE_SIZE);

	this->sprite = Sprite(*tex, frame);
	this->fps = fps;
	this->numFrames = numFrames;
	this->timeElapsed = 0;
	this->currFrame = 0;
}

void Animation::update(Time deltaTime)
{
	this->timeElapsed += deltaTime.asSeconds();
	advance();
}

void Animation::advance() 
{
	// Reduce time to be within [0, 1 / fps)
	float timeBetweenFrames = 1 / (float)fps;

	if (timeElapsed >= timeBetweenFrames)
	{	
		/*
		while (timeElapsed >= timeBetweenFrames)
			timeElapsed -= timeBetweenFrames;
		*/
		timeElapsed = 0;

		currFrame++;

		if (currFrame >= numFrames)
			currFrame = 0;

		frame.left = currFrame * TILE_SIZE;
		sprite.setTextureRect(frame);
	}
}