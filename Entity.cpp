#include "Entity.h"

using namespace std;

GameplayState* Entity::parent = nullptr;
int Entity::global_id = 0;
const int TILE_SIZE = 64;

Entity::Entity() : Entity("UNASSIGNED", 0, 0, nullptr) {}

Entity::Entity(string name, int x, int y, GameplayState* parent) {
	this->position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
	this->animator.sprite.setPosition(position);

	this->name = name;
	this->id = getID();

	this->x = x;
	this->y = y;

	this->parent = parent;
}

Sprite Entity::getSprite() {
	return this->animator.sprite;
}

void Entity::update(Time deltaTime) {
	if (isAnimated)
		this->animator.update(deltaTime);
}

void Entity::setAnimationProperties(Texture* tex, int texX, int texY, int fps, int numFrames) {
	this->animator = Animation(tex, texX, texY);
	
	this->isAnimated = true;
	this->animator.fps = fps;
	this->animator.numFrames = numFrames;
	this->animator.sprite.setPosition(position);
}

void Entity::doAction(std::string action) {
	// Nothing.
}

// private methods

int Entity::getID()
{
	global_id++;
	return global_id - 1;
}
