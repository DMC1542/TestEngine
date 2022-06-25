#pragma once

#include "FeatureState.h"
#include <SFML/Graphics.hpp>

class TestFeature : public FeatureState {
public:
	TestFeature(GameplayState* p);

	void handleInput(sf::Time deltaTime);
	void draw();
	void update();

private:
	sf::RectangleShape shape;
};