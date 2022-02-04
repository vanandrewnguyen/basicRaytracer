#include "texturePolkaDot.h"

Texture::TexturePolkaDot::TexturePolkaDot() {
	// Default is red
	colour1 = qbVector<double>{ std::vector<double>{0.1, 0.1, 0.1, 1.0} };
	colour2 = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0, 1.0} };
}

Texture::TexturePolkaDot::~TexturePolkaDot() {

}

qbVector<double> Texture::TexturePolkaDot::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Apply local transform to uv coord
	qbVector<double> inputUV = uvCoords;
	qbVector<double> newUV = applyTransform(inputUV);
	double newU = newUV.GetElement(0);
	double newV = newUV.GetElement(1);

	// Get local colour and use mod to apply checker pattern
	qbVector<double> localCol{ 4 };
	float intPart;
	int verticalCellID = floor(newV);
	float gridUVX = modf(newU + 4.0 , &intPart) - 0.5;
	float gridUVY = modf(newV + 4.0, &intPart) - 0.5; // equivalent to fract(); in glsl
	float step = 0.0;

	localCol = colour1;
	if (verticalCellID % 2 == 0.0) {
		gridUVX -= 0.5;
		step += NoiseFunctions::smoothstep(radius, radius - blurRad, sqrtf(gridUVX * gridUVX + gridUVY * gridUVY));
		step += NoiseFunctions::smoothstep(radius, radius - blurRad, sqrtf((gridUVX+1.0) * (gridUVX+1.0) + gridUVY * gridUVY));
	} else {
		step += NoiseFunctions::smoothstep(radius, radius - blurRad, sqrtf(gridUVX * gridUVX + gridUVY * gridUVY));
	}
	
	localCol.SetElement(0, colour2.GetElement(0) * step); 
	localCol.SetElement(1, colour2.GetElement(1) * step);
	localCol.SetElement(2, colour2.GetElement(2) * step);

	return localCol;

}

void Texture::TexturePolkaDot::setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2) {
	colour1 = inputCol1;
	colour2 = inputCol2;
}

void Texture::TexturePolkaDot::setRad(float rad, float blur) {
	radius = rad;
	blurRad = blur;
}