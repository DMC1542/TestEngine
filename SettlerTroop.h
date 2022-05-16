#pragma once

#include "Entity.h"

class SettlerTroop : public Entity {
public:
	SettlerTroop(string name, int x, int y) : Entity(name, x, y) {
		// Nothing now
	}
};