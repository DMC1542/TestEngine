#include "SettingsHandler.h"
#include "TextElement.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

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

	in.close();

	// Check to see if first time setup occurred

	in.open("ftsu.start");
	in.getline(line, 29);
	in.close();

	string data = line;
	
	if (data.substr(data.find(":") + 1).compare("false") == 0)
	{
		cout << "Conducting first time setup." << endl;

		sf::VideoMode mode;

		settings["resX"] = mode.getFullscreenModes().at(0).width;
		settings["resY"] = mode.getFullscreenModes().at(0).height;

		ofstream out("config.ini");

		std::map<std::string, int>::iterator it;
		for (it = settings.begin(); it != settings.end(); it++)
		{
			out << it->first << ":" << it->second << std::endl;
		}

		out.close();

		// Update first time setup file (ftsu.start)
		out.open("ftsu.start");
		out << "firstTimeSetupConducted:true";
		out.close();
	}
}