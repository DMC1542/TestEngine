#pragma once

#include "Animation.h"

using namespace std;

enum class EntityType { TEST };

class Entity 
{
public:
	Animation animator;
	string name;
	Vector2f position;
	int id;
	bool isAnimated = false;

	Entity();
	Entity(string name, int x, int y);
	
	void update(Time deltaTime);
	Sprite getSprite();
	void setAnimationProperties(Texture* tex, int texX, int texY, int fps, int numFrames);

private:
	static int global_id;

	int getID();
};