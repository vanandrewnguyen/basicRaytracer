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
	float noiseFBM(int octaves, float x, float y, float amplitude, float freq, int type);

	// These functions are taken from: https://www.shadertoy.com/view/MdScDc | https://www.dreamincode.net/forums/topic/66480-perlin-noise/
	// Credits go to fscur, file accessed on 4/2/22
	// Perlin noise implementation in GLSL, converted in cpp by me
	float perlinNoise(float x, float y);
	float cosLerp(float curr, float dest, float step);

	// Math func
	float clamp(float x, float min, float max);
	float smoothstep(float a, float b, float step);
	float lerp(float curr, float dest, float step);
};

#endif