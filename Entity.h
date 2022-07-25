#pragma once

#include "Actionable.hpp"
#include "Animation.h"
#include <map>

// Forward declaration. Tells compiler this will be defined, just externally.
class GameplayState;

using namespace std;

enum class EntityType { TEST, SETTLER, SETTLEMENT };

class Entity : public Actionable
{
public:
	static GameplayState* parent;

	Animation animator;
	string name;
	Vector2f position;

	int id;
	int x, y;
	bool isAnimated = false;
	vector<string> actions;

	Entity();
	Entity(string name, int x, int y, GameplayState* parent);
	
	void update(Time deltaTime);
	Sprite getSprite();
	void setAnimationProperties(Texture* tex, int texX, int texY, int fps, int numFrames);
	virtual void doAction(std::string action);

private:
	static int global_id;

	int getID();
};