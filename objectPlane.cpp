#include "objectPlane.h"
#include <cmath>

ObjectPlane::ObjectPlane() {

}

ObjectPlane::~ObjectPlane() {

}

bool ObjectPlane::testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
	qbVector<double>& localNormal, qbVector<double>& localColour) {
	// Copy ray and apply backwards transform
	Ray backRay = transformMatrix.applyTransform(castRay, BCKTRANSFORM);

	// Copy vector and normalize
	qbVector<double> k = backRay.currVecAB;
	k.Normalize();

	// Check if there is an intersection, i.e. if cast ray is not parallel to the plane (dot) using Z component
	if (!isFloatCloseEnough(k.GetElement(2), 0.0)) {
		// Does intersection
		double t = backRay.currPointA.GetElement(2) / -k.GetElement(2);

		// If t is negative, then the intersection point must be behind cam, so we ignore
		if (t > 0.0) {
			// In front of camera
			// Get UV coords
			double u = backRay.currPointA.GetElement(0) + (k.GetElement(0) * t);
			double v = backRay.currPointA.GetElement(1) + (k.GetElement(1) * t);

			// If magnitude of both u and v <= 1, then we are in the plane
			if ((fabs(u) < 1.0) && (fabs(v) < 1.0)) {
				// Compute point of intersection
				qbVector<double> pointOfIntersection = backRay.currPointA + t * k; // equation of a line, y = ax + b const and scalar

				// Transform intersection point back in world coord by using fwdmatrix
				intersectionPoint = transformMatrix.applyTransform(pointOfIntersection, FWDTRANSFORM);

				// Get local normal
				qbVector<double> localOrigin{ std::vector<double>{0.0, 0.0, 0.0} };
				qbVector<double> normalVector{ std::vector<double>{0.0, 0.0, -1.0} };
				qbVector<double> globalOrigin = transformMatrix.applyTransform(localOrigin, FWDTRANSFORM);
				localNormal = transformMatrix.applyTransform(normalVector, FWDTRANSFORM) - globalOrigin;
				localNormal.Normalize();

				localColour = baseColour;
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}

	return false;
}