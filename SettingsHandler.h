#pragma once
#include <string>
#include <map>

class SettingsHandler {
public: 
	std::map<std::string, int> settings;

	void getSettings();
};
