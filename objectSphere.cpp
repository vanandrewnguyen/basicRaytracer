#include "objectSphere.h"
#include <cmath>

#define PI 3.1416

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

	// Apply backwards transform to ray (translating world coord to local coord)
	Ray backRay = transformMatrix.applyTransform(castRay, BCKTRANSFORM);

	// Compute values of a, b, c
	qbVector<double> vectorV = backRay.currVecAB;
	vectorV.Normalize();

	// A
	// A will always be of mag 1.0 as it is the squared mag of the casy ray, which is a unit vector.
	// B
	double b = 2.0 * qbVector<double>::dot(backRay.currPointA, vectorV);
	// C
	double c = qbVector<double>::dot(backRay.currPointA, backRay.currPointA) - 1.0;

	// Gives point of intersection in the LOCAL COORDINATE SYSTEM NOT WORLD COORD
	qbVector<double> pointOfIntersection;

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
			pointOfIntersection = ((termA < termB) ? backRay.currPointA + (vectorV * termA) : backRay.currPointA + (vectorV * termB));

			// Transform poi back to world coord
			intersectionPoint = transformMatrix.applyTransform(pointOfIntersection, FWDTRANSFORM);

			// Compute surface normal
			qbVector<double> objectOrigin = qbVector<double>{ std::vector<double>{0.0, 0.0, 0.0} };
			qbVector<double> newObjectOrigin = transformMatrix.applyTransform(objectOrigin, FWDTRANSFORM);
			localNormal = intersectionPoint - newObjectOrigin;
			localNormal.Normalize();

			// Return base colour
			localColour = baseColour;

			// Compute u and v, then store uv coords
			double x = pointOfIntersection.GetElement(0);
			double y = pointOfIntersection.GetElement(1);
			double z = pointOfIntersection.GetElement(2);
			double u = atan(sqrtf(pow(x, 2.0) + pow(y, 2.0)) / z);
			double v = atan(y / x);
			if (x < 0) {
				v += PI;
			}
			// Correct ratio
			u /= PI; 
			v /= PI;
			uvCoords.SetElement(0, u);
			uvCoords.SetElement(1, v);	
		}

		return true;
	} else {
		return false;
	}
}