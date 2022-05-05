#include "Entity.h"
#include "Animation.h"

using namespace std;

Entity::Entity(string name, int x, int y) 
{
	this->position = Vector2f(x, y);

	this->name = name;
	this->id = getID();

	//TODO : DONT HARDCODE. TESTING ONLY
	this->animator = Animation("graphics/animationTest.png", 0, 0, 2, 2);
	this->animator.sprite.setPosition(position);
}

void Entity::update(Time deltaTime)
{
	this->animator.update(deltaTime);
}

// private methods

int Entity::getID()
{
	global_id++;
	return global_id - 1;
}
