#include "SettingsHandler.h"
#include <fstream>
#include <iostream>

using namespace std;

void SettingsHandler::getSettings()
{
	// Initialize the input stream
	ifstream in("config.ini");
	char line[50];

	// Read settings
	while (in.getline(line, 50))
	{
		string data = line;
		string settingName = data.substr(0, data.find(":"));
		int settingValue = stoi(data.substr(data.find(":") + 1));

		settings[settingName] = settingValue;
	}
}