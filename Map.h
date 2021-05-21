#pragma once
#include <vector>

using namespace std;

class Map
{
public:
	int width;
	int height;
	vector<vector<double>> noiseValues;

	Map();
	Map(int width, int height);
};