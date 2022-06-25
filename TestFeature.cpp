#include "TestFeature.h"
#include "GameplayState.h"

TestFeature::TestFeature(GameplayState* parent) {
	this->parent = parent;

	shape = sf::RectangleShape(sf::Vector2f(500, 500));
	shape.setPosition(500, 500);
	shape.setFillColor(Color::Red);
}

void TestFeature::handleInput(sf::Time deltaTime) {
	sf::Event event;

	// Allow for normal movement
	parent->applyWASDmovement(deltaTime);

	// Poll for events
	while (parent->game->window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape) {
				parent->featureStates.pop();
				break;
			} else 
				parent->applyNormalKeybinds(event.key.code);
		}
	}
}

void TestFeature::draw() {
	parent->game->window.draw(shape);
}

void TestFeature::update() {

}