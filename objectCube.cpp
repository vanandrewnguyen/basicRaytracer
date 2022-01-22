#include "objectCube.h"
#include <cmath>

ObjectCube::ObjectCube() {

}

ObjectCube::~ObjectCube() {

}

bool ObjectCube::testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
	qbVector<double>& localNormal, qbVector<double>& localColour) {
	// Copy ray and apply back transform
	Ray backRay = transformMatrix.applyTransform(castRay, BCKTRANSFORM);

	// Get values of a
	// In the line equation x = a + t * k where x is a line vector, a is a point, t is a scalar, k is a direction vector
	double ax = backRay.currPointA.GetElement(0);
	double ay = backRay.currPointA.GetElement(1);
	double az = backRay.currPointA.GetElement(2);

	/*
	Plane in vector form is x = p_0 + p_1 * u + p_2 * v
	So equating both for a line-plane intersection: a + t * k = p_0 + p_1 * u + p_2 * v
	Rearrange for a gives you a vector mulitiplication (1x3 * 3x1)
	*/
	// Get value of k
	qbVector<double> k = backRay.currVecAB;
	k.Normalize();
	double kx = k.GetElement(0);
	double ky = k.GetElement(1);
	double kz = k.GetElement(2);

	// Test for intersecton with each plane
	

	return false;
}