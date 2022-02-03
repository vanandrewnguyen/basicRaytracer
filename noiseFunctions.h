#ifndef NOISEFUNC_H
#define NOISEFUNC_H

#include <math.h>
#include <algorithm>

namespace NoiseFunctions {
	// These functions are taken from: https://github.com/SRombauts/SimplexNoise/blob/master/src/SimplexNoise.cpp
	// Credits go to Sebastien Rombauts, file accessed on 3/2/22
	// Simplex Noise implementation in cpp

	uint8_t hash(int32_t i);
	float gradient2D(int32_t hash, float x, float y);
	float noise(float x, float y);
	float noiseFBM(int octaves, float x, float y, float amplitude, float freq);

	float clamp(float x, float min, float max);
	float smoothstep(float a, float b, float step);
};

#endif