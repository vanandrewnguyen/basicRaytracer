#include "textureBase.h"
#include <math.h>

Texture::TextureBase::TextureBase() {
}

Texture::TextureBase::~TextureBase() {

}

qbVector<double> Texture::TextureBase::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Set output vector (4d since RGBA)
	qbVector<double> outputCol{ 4 };

	return outputCol;

}

void Texture::TextureBase::setTransform(const qbVector<double>& translation, const double rotation, const qbVector<double>& scale) {
	// Build transform matrix
	qbMatrix2<double> rotationMatrix = { 3, 3, std::vector<double> {cos(rotation), -sin(rotation), 0.0, sin(rotation), cos(rotation), 0.0, 0.0, 0.0, 1.0} };
	qbMatrix2<double> scaleMatrix = { 3, 3, std::vector<double> {scale.GetElement( 0), 0.0, 0.0, 0.0, scale.GetElement(1), 0.0, 0.0, 0.0, 1.0} };
	qbMatrix2<double> translationMatrix = { 3, 3, std::vector<double> {1.0, 0.0, translation.GetElement(0), 0.0, 1.0, translation.GetElement(1), 0.0, 0.0, 1.0} };
	// Combine to form final matrix
	transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

qbVector<double> Texture::TextureBase::blend4DColoursTo3D(const std::vector<qbVector<double>>& inputColourList) {
	// Set output col (RGB)
	qbVector<double> outputCol{ 3 };

	return outputCol;
}

qbVector<double> Texture::TextureBase::applyTransform(const qbVector<double>& inputVector) {
	// Copy input vec and merge 4D to 3D elements
	qbVector<double> newInput{ 3 };
	newInput.SetElement(0, inputVector.GetElement(0));
	newInput.SetElement(1, inputVector.GetElement(1));

	qbVector<double> result = transformMatrix * newInput;

	// Output
	qbVector<double> output{ 2 };
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));
	return output;
}

