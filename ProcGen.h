#pragma once

#include "Noise.h"
#include "Map.h"

class ProcGen
{
public:
	static Map generateMap(int width, int height, int64_t seed);

private: 
	static double invLerp(double min, double max, double value);
};