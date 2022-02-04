#include "texturePerlin.h"

Texture::TexturePerlin::TexturePerlin() {
	// Default is red
	colour = qbVector<double>{ std::vector<double>{0.1, 0.1, 0.1, 1.0} };
}

Texture::TexturePerlin::~TexturePerlin() {

}

qbVector<double> Texture::TexturePerlin::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Apply local transform to uv coord
	qbVector<double> inputUV = uvCoords;
	qbVector<double> newUV = applyTransform(inputUV);
	double newU = newUV.GetElement(0);
	double newV = newUV.GetElement(1);

	// Get local colour
	qbVector<double> localCol{ 4 };
	float noiseInt = NoiseFunctions::smoothstep(0.2, -0.2, abs(NoiseFunctions::noiseFBM(4, newU, newV, 1.0, 2.0, 1)));
	localCol = colour * noiseInt;

	return localCol;

}

void Texture::TexturePerlin::setColour(const qbVector<double>& inputCol) {
	colour = inputCol;
}