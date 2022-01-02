#include "objectSphere.h"
#include <cmath>

// Constructor destructor
ObjectSphere::ObjectSphere() {

}

ObjectSphere::~ObjectSphere() {

}

bool ObjectSphere::testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
	qbVector<double>& localNormal, qbVector<double>& localColour) {
	// Solving quadratic equations derived form length of a point (sqrt(x^2 + y^2 + z^2)) which can be converted into
	// vector form, which can be simplified further.
	// You end up with a quadratic formula.

	// Compute values of a, b, c
	qbVector<double> vectorV = castRay.currVecAB;
	vectorV.Normalize();

	// A
	// A will always be of mag 1.0 as it is the squared mag of the casy ray, which is a unit vector.
	// B
	double b = 2.0 * qbVector<double>::dot(castRay.currPointA, vectorV);
	// C
	double c = qbVector<double>::dot(castRay.currPointA, castRay.currPointA) - 1.0;

	// Test for intersection (this is the determinant, since if the quadratic doesn't exist then there is no intersection)
	double intersectTest = (b * b) - 4.0 * c;
	if (intersectTest > 0.0) {
		double determinant = sqrtf(intersectTest);
		double termA = (-b + determinant) / 2.0;
		double termB = (-b - determinant) / 2.0;

		// If tA or tB are negative, this means that some part of the object is behind the camera so we ignore it
		if ((termA < 0.0) || (termB < 0.0)) {
			return false;
		} else {
			// Determine point of intersection (update pointer of intersectPoint)
			// Start point + direction vector * scale
			intersectionPoint = ((termA < termB) ? castRay.currPointA + (vectorV * termA) : castRay.currPointA + (vectorV * termB));
		}
			
		return true;
	} else {
		return false;
	}
}