#include "geometricTransform.h"

GeometricTransform::GeometricTransform() {
	// Set transforms to identity matrices (no change)
	forwardTransform.SetToIdentity();
	backwardTransform.SetToIdentity();
}

GeometricTransform::~GeometricTransform() {

}

GeometricTransform::GeometricTransform(const qbMatrix2<double>& forward, const qbMatrix2<double>& backward) {
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
	return forwardTransform;
}

qbMatrix2<double> GeometricTransform::getBackwardMatrix() {
	return backwardTransform;
}

Ray GeometricTransform::applyTransform(const Ray& inputRay, bool directionFlag) {
	// Create output
	Ray outputRay;
	// Use forward / backwards transform
	// this is a pointer to all member functions, the object is referencing its own address
	outputRay.currPointA = this->applyTransform(inputRay.currPointA, (directionFlag) ? FWDTRANSFORM : BCKTRANSFORM);
	outputRay.currPointB = this->applyTransform(inputRay.currPointB, (directionFlag) ? FWDTRANSFORM : BCKTRANSFORM);
	outputRay.currVecAB = outputRay.currPointB - outputRay.currPointA;

	return outputRay;
}

qbVector<double> GeometricTransform::applyTransform(const qbVector<double>& inputVector, bool directionFlag) {
	// Convert input vector into a 4 dimensional vector
	std::vector<double> temp{ inputVector.GetElement(0), inputVector.GetElement(1), inputVector.GetElement(2), 1.0 };
	qbVector<double> tempVector{ temp };

	// Resultant vector
	qbVector<double> resultantVector;
	resultantVector = (directionFlag) ? forwardTransform * tempVector : backwardTransform * tempVector;

	// Change back into three dimensional vector
	qbVector<double> outputVector {std::vector<double> {resultantVector.GetElement(0), resultantVector.GetElement(1), resultantVector.GetElement(2)}};
	return outputVector;
}

GeometricTransform operator* (const GeometricTransform& lhs, const GeometricTransform& rhs) {
	// Get product of the two forward transforms (left and right matrices)
	qbMatrix2<double> forwardResult = lhs.forwardTransform * rhs.forwardTransform;

	// Compute bcktrnsfm as inverse of fwdtrnsfm
	qbMatrix2<double> backwardResult = forwardResult;
	backwardResult.Inverse();

	// Final result using constructor (overload version)
	GeometricTransform result (forwardResult, backwardResult);
	return result;
}

// Overload assignment operator
GeometricTransform GeometricTransform::operator = (const GeometricTransform& rhs) {
	// Make sure we are not assigning to self
	if (this != &rhs) {
		forwardTransform = rhs.forwardTransform;
		backwardTransform = rhs.backwardTransform;
	}
	// Return ptr address to self
	return *this;
}

void GeometricTransform::printMatrix(bool directionFlag) {
	if (directionFlag) {
		print(forwardTransform);
	} else {
		print(backwardTransform);
	}
}

void GeometricTransform::print(const qbMatrix2<double>& matrix) {
	// Get rows and cols from matrix
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	for (int row = 0; row < nRows; ++row) {
		for (int col = 0; col < nCols; ++col) {
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
		}
		// new line
		std::cout << std::endl;
	}
}

void GeometricTransform::printVector(const qbVector<double>& vector) {
	int nRows = vector.GetNumDims();
	for (int row = 0; row < nRows; ++row) {
		std::cout << std::fixed << std::setprecision(3) << vector.GetElement(row) << std::endl;
	}
}