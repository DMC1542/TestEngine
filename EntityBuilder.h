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
		Entity* temp = nullptr;

		if (type == EntityType::TEST)
		{
			temp = new TestEntity(name, x, y, gameplayState);
			temp->setAnimationProperties(&rManager->get("graphics/animationTest.png"), 0, 0, 1, 2);
		}
		else if (type == EntityType::SETTLER)
		{
			temp = new SettlerTroop(name, x, y, gameplayState);
			temp->setAnimationProperties(&rManager->get("graphics/Entities/settlerTroop.png"), 0, 0, 2, 3);
		} 
		else if (type == EntityType::SETTLEMENT) {
			temp = new PrimitiveSettlement(name, x, y, gameplayState);
			temp->setAnimationProperties(&rManager->get("graphics/Entities/settlement.png"), 0, 0, 1, 1);
			temp->isAnimated = false;
		}

		return temp;
	}
};