#pragma once

#include "Entity.h"

class TestEntity : public Entity {
public:
	TestEntity(string name, int x, int y, GameplayState* parent) : Entity(name, x, y, parent) {
		// Eventually, testing code.
	}
};