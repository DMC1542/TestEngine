#include "ProcGen.h"
#include <iostream>

using namespace std;

Map ProcGen::generateMap(int width, int height, int64_t seed)
{
	cout << "Starting procedural map generation" << endl;

	Noise::Noise noiseGenerator(seed);
	Map map(width, height);

	// Arbitrary values
	double x = -.5, y = -.5;
	double minNoise = DBL_MAX, maxNoise = DBL_MIN;

	for (int height = 0; height < map.height; height++)
	{
		vector<double> row; 

		for (int width = 0; width < map.width; width++)
		{
			x += .05;

			double noise = noiseGenerator.eval(x, y);   // Octave 1
			noise += noiseGenerator.eval(2 * x, 2 * y); // Octave 2
			noise += noiseGenerator.eval(4 * x, 4 * y); // Octave 3
			noise += noiseGenerator.eval(8 * x, 8 * y); // Octave 4

			if (noise < minNoise)
				minNoise = noise;
			if (noise > maxNoise)
				maxNoise = noise;

			row.push_back(noise);
		}

		map.noiseValues.push_back(row);
		y += .05;
		x = -.5;
	}

	for (int h = 0; h < map.height; h++)
	{
		for (int w = 0; w < map.width; w++)
		{
			map.noiseValues[h][w] = invLerp(minNoise, maxNoise, map.noiseValues[h][w]);
		}
	}

	return map;
}

// This normalizes value between the min and max (returns a value between 0 and 1)
double ProcGen::invLerp(double min, double max, double value)
{
	return (value - min) / (max - min);
}