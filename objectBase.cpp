#include "objectBase.h"
#include <math.h>

#define EPSILON 1e-21f;

// Constructor destructor
ObjectBase::ObjectBase() {

}

ObjectBase::~ObjectBase() {

}

// Checks intersection for object
bool ObjectBase::testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
	qbVector<double>& localNormal, qbVector<double>& localColour) {
	return false;
}

// Checks if two numbers are close enough to consider being the same
bool ObjectBase::isFloatCloseEnough(const double n1, const double n2) {
	return fabs(n1 - n2) < EPSILON;
}
