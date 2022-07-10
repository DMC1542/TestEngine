#pragma once

#include "Animation.h"
#include <map>

// Forward declaration. Tells compiler this will be defined, just externally.
class GameplayState;

using namespace std;

enum class EntityType { TEST, SETTLER, SETTLEMENT };

class Entity 
{
public:
	Animation animator;
	string name;
	Vector2f position;
	map< string, void(*)(GameplayState*)> actionList;

	int id;
	int x, y;
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