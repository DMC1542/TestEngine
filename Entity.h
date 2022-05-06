#pragma once

#include "Animation.h"

using namespace std;

class Entity 
{
public:
	Animation animator;
	string name;
	Vector2f position;
	int id;

	Entity(string name, Texture* tex, int x, int y);
	void update(Time deltaTime);
	Sprite getSprite();

private:
	static int global_id;

	int getID();
};