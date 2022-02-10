#include "textureCellular.h"

#define PI 3.1416

Texture::TextureCellular::TextureCellular() {
	// Default is red
	colour = qbVector<double>{ std::vector<double>{0.1, 0.1, 0.1, 1.0} };
}

Texture::TextureCellular::~TextureCellular() {

}

qbVector<double> Texture::TextureCellular::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Apply local transform to uv coord
	qbVector<double> inputUV = uvCoords;
	qbVector<double> newUV = applyTransform(inputUV);
	double newU = newUV.GetElement(0);
	double newV = newUV.GetElement(1);

	// Get local colour and use mod to apply checker pattern
	qbVector<double> localCol{ 4 };

	float intPart;
	float horizontalCellID = floor(newU);	
	float verticalCellID = floor(newV);
	float gridUVX = modf(newU + 4.0, &intPart) - 0.5;
	float gridUVY = modf(newV + 4.0, &intPart) - 0.5;
	/*
	float pX = NoiseFunctions::random(horizontalCellID);
	float pY = NoiseFunctions::random(verticalCellID);
	float distDifference = sqrtf(pow(pX - gridUVX, 2.0) + pow(pY - gridUVY, 2.0));
	*/

	// Loop through neighbours of curr cell
	float minimumDist = 1.0;
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			float neighbourX = float(x);
			float neighbourY = float(y);

			// Get rand point
			float pX = NoiseFunctions::hash(horizontalCellID + neighbourX) / 255.0;
			float pY = NoiseFunctions::hashRev(verticalCellID + neighbourY) / 255.0;
			float staticTime = 10.0;

			// Animate points
			pX = 0.5 + 0.9 * sin(staticTime + 2 * PI * pX * pY);
			pY = 0.5 + 0.9 * cos(staticTime + 2 * PI * pY * pX);

			// Get distance between center of cell and rand point
			float distDifference = sqrtf(pow(neighbourX + pX - gridUVX, 2.0) + pow(neighbourY + pY - gridUVY, 2.0));
			minimumDist = std::min(minimumDist, distDifference);

		}
	}

	//std::cout << "pX: " << pX << " | pY: " << pY << std::endl;

	//localCol = colour * minimumDist;
	localCol.SetElement(0, localCol.GetElement(0) + colour.GetElement(0) * minimumDist);
	localCol.SetElement(1, localCol.GetElement(1) + colour.GetElement(1) * minimumDist);
	localCol.SetElement(2, localCol.GetElement(2) + colour.GetElement(2) * minimumDist);

	return localCol;

}

void Texture::TextureCellular::setColour(const qbVector<double>& inputCol) {
	colour = inputCol;
}