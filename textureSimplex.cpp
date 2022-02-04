#include "textureSimplex.h"

Texture::TextureSimplex::TextureSimplex() {
	// Default is red
	colour1 = qbVector<double>{ std::vector<double>{0.1, 0.1, 0.1, 1.0} };
	colour2 = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0, 1.0} };
}

Texture::TextureSimplex::~TextureSimplex() {

}

qbVector<double> Texture::TextureSimplex::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Apply local transform to uv coord
	qbVector<double> inputUV = uvCoords;
	qbVector<double> newUV = applyTransform(inputUV);
	double newU = newUV.GetElement(0);
	double newV = newUV.GetElement(1);

	// Get local colour
	qbVector<double> localCol{ 4 };
	// Get simplex noise 
    float noiseInt = NoiseFunctions::smoothstep(0.0, 0.4, abs(NoiseFunctions::noiseFBM(4, newU, newV, 1.0, 1.0, 0)));
	localCol.SetElement(0, NoiseFunctions::lerp(colour1.GetElement(0), colour2.GetElement(0), noiseInt));
	localCol.SetElement(1, NoiseFunctions::lerp(colour1.GetElement(1), colour2.GetElement(1), noiseInt));
	localCol.SetElement(2, NoiseFunctions::lerp(colour1.GetElement(2), colour2.GetElement(2), noiseInt));
	localCol.SetElement(3, 1.0);

	return localCol;

}

void Texture::TextureSimplex::setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2) {
	colour1 = inputCol1;
	colour2 = inputCol2;
}