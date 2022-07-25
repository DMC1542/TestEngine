#pragma once

#include "Entity.h"

class PrimitiveSettlement : public Entity {
public:
	PrimitiveSettlement(string name, int x, int y, GameplayState* parent) : Entity(name, x, y, parent) {
		// Nothing yet
	}
};