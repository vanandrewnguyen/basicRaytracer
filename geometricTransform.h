#ifndef GEOMETRICTRANSFORM_H
#define GEOMETRICTRANSFORM_H

#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"

// Constants
// Def direction flag values (apply transformation backwards or forwards)
constexpr bool FWDTRANSFORM = true;
constexpr bool BCKTRANSFORM = false;

class GeometricTransform {
public:
	// Constructor destructor
	GeometricTransform();
	~GeometricTransform();

	// Construct from pair of matrices
	void GTForm(const qbMatrix2<double> &forward, const qbMatrix2<double> &backward);

	// Set translation, scale, rotation
	void setTransform(const qbVector<double>& translation, const qbVector<double>& scale, const qbVector<double>& rotation);

	// Getter for transform matrices
	qbMatrix2<double> getForwardMatrix();
	qbMatrix2<double> getBackwardMatrix();

	// Setter for transform matrices (overload with two functions, changes output data type)
	Ray applyTransform(const Ray& inputRay, bool directionFlag);
	qbVector<double> applyTransform(const qbVector<double> &inputVector, bool directionFlag);

	// Overload operators
	// Define as friend meaning it has access to class's private members
	friend GeometricTransform operator* (const GeometricTransform &lhs, const GeometricTransform &rhs);
	// Overload assignment operator
	GeometricTransform operator = (const GeometricTransform& rhs);

	// Print transform matrix to STDOUT
	void printMatrix(bool dirFlag);

	// Allow printing of vectors
	static void printVector(const qbVector<double>& vector);

private:
	void print(const qbMatrix2<double>& matrix);

private:
	qbMatrix2<double> forwardTransform{ 4, 4 };
	qbMatrix2<double> backwardTransform{ 4, 4 };
};


#endif
