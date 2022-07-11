#pragma once

#include "FeatureState.h"
#include "ActionMenu.h"

// Forward declaration
class GameplayState;

class ActionSelection : public FeatureState {
public:
	ActionSelection(GameplayState* p);

	void handleInput(sf::Time deltaTime);
	void draw();
	void update();

private:
	ActionMenu actionMenu;
};