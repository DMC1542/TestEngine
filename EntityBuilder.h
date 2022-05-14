#pragma once

#include "Entity.h"
#include "TilesetHandler.h"
#include "TestEntity.h"

class EntityBuilder {
public:
	TilesetHandler* tHandler;

	EntityBuilder() {}

	EntityBuilder(TilesetHandler* tHandler) {
		this->tHandler = tHandler;
	}

	Entity* buildEntity(EntityType type, string name, int x, int y)
	{
		Entity* temp;

		if (type == EntityType::TEST)
		{
			temp = new TestEntity(name, x, y);
			temp->setAnimationProperties(&tHandler->animationTEST, 0, 0, 1, 2);
		}

		return temp;
	}
};