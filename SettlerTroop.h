#pragma once

#include "Entity.h"

/*
Plan: 
	Each entity has a list of strings that demonstrate it's actions
	This is passed to the ActionSelection class in it's entirety.

	The method to be called by each class should be an override of a method specified by an interface. something like void doAction(std::string action); 
		where the string specifies exactly what action to be taken. We have a massive switch case / if train
	
	Each button will hold the string name of the function, so that it can be called within the child class.
*/

class SettlerTroop : public Entity {
public:
	SettlerTroop(string name, int x, int y, GameplayState* gameplayState) : Entity(name, x, y, gameplayState) {
		std::string placeSettlementText= "placeSettlement";

		actions.push_back("placeSettlement");
	}
	
	void placeSettlement();
	
	virtual void doAction(std::string action);
private: 
};