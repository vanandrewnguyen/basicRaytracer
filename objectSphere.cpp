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

	/*
	<x, y, z> = <px, py, pz> + <vx, vy, vz>
	where x = p + t * v where t is a scalar
	hence using the length formula we get x^2 + y^2 + z^2 = r^2 where x = p + t * v, y = ... etc
	therefore, r^2 = (px + t*v)^2 + (py + t*v)^2 + (pz + t*v)^2
	Solve for t.
	By expanding and simplifying we rearrange to get 
	t^2(v . v) + 2*t*(p . v) + (p . p) - r^2 = 0,
	where this is a quadratic formula with a*t^2 + b*t + c = 0, where a, b, c = ... (compare coefficients)
	*/

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
		
		// Compute surface normal
		localNormal = intersectionPoint;
		localNormal.Normalize();

		return true;
	} else {
		return false;
	}
}