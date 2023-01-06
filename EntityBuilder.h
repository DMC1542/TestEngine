#pragma once

#include "Entity.h"
#include "ResourceManager.h"
#include "TestEntity.h"
#include "SettlerTroop.h"
#include "PrimitiveSettlement.h"

class EntityBuilder {
public:
	ResourceManager<Texture>* rManager;

	EntityBuilder() {}

	EntityBuilder(ResourceManager<Texture>* rManager) {
		this->rManager = rManager;
	}

	Entity* buildEntity(EntityType type, string name, int x, int y, GameplayState* gameplayState)
	{
		Entity* temp = new Entity(name, x, y, gameplayState);

		if (type == EntityType::TEST)
		{
			delete temp;
			temp = new TestEntity(name, x, y, gameplayState);
			temp->setAnimationProperties(&rManager->get("graphics/animationTest.png"), 0, 0, 1, 2);
		}
		else if (type == EntityType::SETTLER)
		{
			delete temp;
			temp = new SettlerTroop(name, x, y, gameplayState);
			temp->setAnimationProperties(&rManager->get("graphics/Entities/settlerTroop.png"), 0, 0, 2, 3);
		} 
		else if (type == EntityType::SETTLEMENT) {
			delete temp;
			temp = new PrimitiveSettlement(name, x, y, gameplayState);
			temp->setAnimationProperties(&rManager->get("graphics/Entities/settlerTroop.png"), 0, 0, 1, 1);
			temp->isAnimated = false;
		}

		return temp;
	}
};