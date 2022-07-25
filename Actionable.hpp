#pragma once

#include <string>

class Actionable {
public:
	virtual void doAction(std::string action) = 0;
};