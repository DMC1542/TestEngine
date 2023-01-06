#include "SettlerTroop.h"
#include "GameplayState.h"
#include <string>

void SettlerTroop::placeSettlement() {
	// First, create the settlement, then remove the settler. Order matters - we need x,y from settler
	Tile* currentTile = parent->getTile(x, y);
	parent->createEntity(EntityType::SETTLEMENT, "Settlement", x, y);
	parent->deleteEntity(this->id);
}

void SettlerTroop::doAction(std::string action) {
	if (action.compare("placeSettlement") == 0) {
		placeSettlement();
	}
}