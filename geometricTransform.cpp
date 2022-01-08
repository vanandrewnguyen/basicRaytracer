#include "geometricTransform.h"

GeometricTransform::GeometricTransform() {
	// Set transforms to identity matrices (no change)
	forwardTransform.SetToIdentity();
	backwardTransform.SetToIdentity();
}

GeometricTransform::~GeometricTransform() {

}

void GeometricTransform::GTForm(const qbMatrix2<double>& forward, const qbMatrix2<double>& backward) {
	// Check inputs are 4x4 matrices (transformation + translation, translation is the last column)
	if ((forward.GetNumRows() != 4) || (backward.GetNumRows() != 4) || (forward.GetNumCols() != 4) || (backward.GetNumCols() != 4)) {
		throw std::invalid_argument("Geometric transform inputs are not all 4x4 matrices.");
	}

	// Set class member matrices
	forwardTransform = forward;
	backwardTransform = backward;

}

void GeometricTransform::setTransform(const qbVector<double>& translation, const qbVector<double>& scale, const qbVector<double>& rotation) {
	// Define matrix for each component of the transform
	qbMatrix2<double> translationMatrix{ 4,4 };
	qbMatrix2<double> rotationMatrixX{ 4,4 };
	qbMatrix2<double> rotationMatrixY{ 4,4 };
	qbMatrix2<double> rotationMatrixZ{ 4,4 };
	qbMatrix2<double> scaleMatrix{ 4,4 };

	// Set all to identity
	translationMatrix.SetToIdentity();
	rotationMatrixX.SetToIdentity();
	rotationMatrixY.SetToIdentity();
	rotationMatrixZ.SetToIdentity();
	scaleMatrix.SetToIdentity();

	// Convert matrices to given arguments //

	// Translation
	/*
	[1, 0, 0, x]
	[0, 1, 0, y]
	[0, 0, 1, z]
	[0, 0, 0, 1]
	*/
	translationMatrix.SetElement(0, 3, translation.GetElement(0)); // 1st row 4th column
	translationMatrix.SetElement(1, 3, translation.GetElement(1)); // 2nd row
	translationMatrix.SetElement(2, 3, translation.GetElement(2)); // 3rd row

	// Rotation X
	/*
	[1, 0, 0, 0]
	[0, cos(x), -sin(x), 0]
	[0, sin(x), cos(x), 0]
	[0, 0, 0, 1]
	*/
	rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
	rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

	// Rotation Y
	/*
	[cos(y), 0, sin(y), 0]
	[0, 1, 0, 0]
	[-sin(y), 0, cos(y), 0]
	[0, 0, 0, 1]
	*/
	rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
	rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

	// Rotation Z
	/*
	[cos(z), -sin(z), 0, 0]
	[sin(z), cos(z), 0, 0]
	[0, 0, 1, 0]
	[0, 0, 0, 1]
	*/
	rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

	// Scale
	scaleMatrix.SetElement(0, 0, scale.GetElement(0));
	scaleMatrix.SetElement(1, 1, scale.GetElement(1));
	scaleMatrix.SetElement(2, 2, scale.GetElement(2));

	// Multiply all matrices to give final forward matrix (since matrices add values on multiplication)
	forwardTransform = translationMatrix * scaleMatrix * rotationMatrixX * rotationMatrixY * rotationMatrixZ;
	backwardTransform = forwardTransform;
	backwardTransform.Inverse(); // we can inverse a matrix to get one that points in the opposite direction, like a negative vector
}

qbMatrix2<double> GeometricTransform::getForwardMatrix() {

}

qbMatrix2<double> GeometricTransform::getBackwardMatrix() {

}

Ray GeometricTransform::applyTransform(const Ray& inputRay, bool directionFlag) {

}

qbVector<double> GeometricTransform::applyTransform(const qbVector<double>& inputVector, bool directionFlag) {

}

//friend GeometricTransform operator* (const GeometricTransform& lhs, const GeometricTransform& rhs);

//GeometricTransform operator = (const GeometricTransform& rhs);

void GeometricTransform::printMatrix(bool dirFlag) {

}

void GeometricTransform::printVector(const qbVector<double>& vector) {

}