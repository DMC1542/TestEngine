#pragma once

#include "Entity.h"

class TestEntity : public Entity{
public:
	TestEntity(string name, int x, int y) : Entity(name, x, y) {
		// Eventually, testing code.
	}
};