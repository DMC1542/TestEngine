#pragma once

#include "Entity.h"
#include "TilesetHandler.h"
#include "TestEntity.h"
#include "SettlerTroop.h"
#include "PrimitiveSettlement.h"

class EntityBuilder {
public:
	TilesetHandler* tHandler;

	EntityBuilder() {}

	EntityBuilder(TilesetHandler* tHandler) {
		this->tHandler = tHandler;
	}

	Entity* buildEntity(EntityType type, string name, int x, int y)
	{
		Entity* temp = new Entity(name, x, y);

		if (type == EntityType::TEST)
		{
			delete temp;
			temp = new TestEntity(name, x, y);
			temp->setAnimationProperties(&tHandler->animationTEST, 0, 0, 1, 2);
		}
		else if (type == EntityType::SETTLER)
		{
			delete temp;
			temp = new SettlerTroop(name, x, y);
			temp->setAnimationProperties(&tHandler->settlerTroopTexture, 0, 0, 2, 3);
		} 
		else if (type == EntityType::SETTLEMENT) {
			delete temp;
			temp = new PrimitiveSettlement(name, x, y);
			temp->setAnimationProperties(&tHandler->settlementTexture , 0, 0, 1, 1);
			temp->isAnimated = false;
		}

		return temp;
	}
};