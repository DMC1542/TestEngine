#pragma once

#include "Noise.h"

class ProcGen
{
public:
	static Map generateMap(int width, int height, int64_t seed, int octaves, double scale, double persistence, double lacunarity);

private: 
	static double invLerp(double min, double max, double value);
};