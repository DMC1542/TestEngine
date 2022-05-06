#include "Entity.h"
#include "Animation.h"

using namespace std;

int Entity::global_id = 0;

Entity::Entity(string name, Texture* tex, int x, int y) 
{
	this->position = Vector2f(x, y);

	this->name = name;
	this->id = getID();

	//TODO : DONT HARDCODE. TESTING ONLY
	this->animator = Animation(tex, 0, 0, 1, 2);
	this->animator.sprite.setPosition(position);

	return;
}

void Entity::update(Time deltaTime)
{
	this->animator.update(deltaTime);
}

Sprite Entity::getSprite()
{
	return animator.sprite;
}

// private methods

int Entity::getID()
{
	global_id++;
	return global_id - 1;
}
