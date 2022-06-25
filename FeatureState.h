#pragma once

// Forward declaration. Tells compiler this will be defined, just externally.
class GameplayState;

class FeatureState {

public:
	enum ControlType {
		TOTAL_CONTROL = 0x01,
		SELECTIVE_CONTROL = 0x02,
		TOTAL_PASSTHROUGH = 0x04
	};

	unsigned char control_type;

	FeatureState(GameplayState* g) {
		parent = g;
	}

	virtual void handleInput(Time deltaTime) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;

private:
	GameplayState* parent;
};