#include "textureStripe.h"

Texture::TextureStripe::TextureStripe() {
	// Default is red
	colour1 = qbVector<double>{ std::vector<double>{0.1, 0.1, 0.1, 1.0} };
	colour2 = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0, 1.0} };
}

Texture::TextureStripe::~TextureStripe() {

}

qbVector<double> Texture::TextureStripe::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Apply local transform to uv coord
	qbVector<double> inputUV = uvCoords;
	qbVector<double> newUV = applyTransform(inputUV);
	double newU = newUV.GetElement(0);
	double newV = newUV.GetElement(1);

	// Get local colour and use mod to apply checker pattern
	qbVector<double> localCol{ 4 };
	int check = static_cast<int>(floor(newV));
	localCol = ((check % 2) == 0) ? colour2 : colour1;

	return localCol;

}

void Texture::TextureStripe::setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2) {
	colour1 = inputCol1;
	colour2 = inputCol2;
}