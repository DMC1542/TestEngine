#pragma once

#include "Entity.h"

class SettlerTroop : public Entity {
public:
	SettlerTroop(string name, int x, int y) : Entity(name, x, y) {
		std::string placeSettlementText= "Place Settlement";
		void(*callback)(GameplayState*);
		//solution: instead provide the buttons for the actionSelection
		callback = &placeSettlement;
		actionList.insert(std::pair<string, void(*)(GameplayState*)>(placeSettlementText, &placeSettlement));
	}

	void placeSettlement(GameplayState*);
private: 
};