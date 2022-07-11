#include "SettlerTroop.h"
#include "GameplayState.h"

void SettlerTroop::placeSettlement(GameplayState* gameplayState) {
	// First, create the settlement, then remove the settler. Order matters - we need x,y from settler
	Tile* currentTile = gameplayState->getTile(x, y);
	gameplayState->createEntity(EntityType::SETTLEMENT, "Settlement", x, y);
	gameplayState->deleteEntity(id);
}