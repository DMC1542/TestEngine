#pragma once

#include "SFML/System/Time.hpp"

// Forward declaration. Tells compiler this will be defined, just externally.
class GameplayState;

class FeatureState {
public:	
	/**
	 * @brief Handles the input for a mechanical feature
	 * @param deltaTime Time since last frame in seconds
	 * @return Only relevant ControlType != TOTAL_CONTROL. True: keypress passthrough. False: Trap keypress.
	*/
	virtual void handleInput(sf::Time deltaTime) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

	GameplayState* parent = nullptr;
};