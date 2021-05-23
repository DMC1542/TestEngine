#include "ProcGen.h"
#include <iostream>

using namespace std;

// Octaves: Number of iterations to generate finer details (0, inf)
// Persistence: Controls amplitude (Decreases in amplitude as persistence increases) (0, 1]
// Lacunarity: Controls frequency (Increases in frequency as lacunarity increases) [1, inf)
// Scale: Determines the fractional increase for each XY coord. ATLEAST 20 for 1/20 steps.
Map ProcGen::generateMap(int width, int height, int64_t seed, 
	int octaves, double scale, double persistence, double lacunarity)
{
	cout << "Starting procedural map generation" << endl;

	Noise::Noise noiseGenerator(seed);
	Map map(width, height);

	double x, y;
	double minNoise = DBL_MAX, maxNoise = DBL_MIN;

	// Ensure that scale is not <= 0
	if (scale <= 0)
		scale = .001;

	for (int height = 0; height < map.height; height++)
	{
		vector<double> row; 

		for (int width = 0; width < map.width; width++)
		{
			double frequency = 1, amplitude = 1, noiseHeight = 0, noise;

			// Do octaves
			for (int i = 0; i < octaves; i++)
			{
				x = (double)width / scale * frequency;
				y = (double)height / scale * frequency;

				noise = noiseGenerator.eval(x, y); // * 2 - 1, IF it returns values from 0:1 to get -1:1

				// Now using the perlin value, modify amplitude
				noiseHeight += noise * amplitude;

				amplitude *= persistence;
				frequency *= lacunarity;
			}

			if (noiseHeight< minNoise)
				minNoise = noiseHeight;
			if (noiseHeight > maxNoise)
				maxNoise = noiseHeight;

			row.push_back(noiseHeight);
		}

		map.noiseValues.push_back(row);
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