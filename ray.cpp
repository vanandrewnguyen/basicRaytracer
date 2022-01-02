#include "ray.h"

Ray::Ray(const qbVector<double>& pointA, const qbVector<double>& pointB) {
	currPointA = pointA;
	currPointB = pointB;
	currVecAB = pointB - pointA;
}

qbVector<double> Ray::getPointA() const {
	return currPointA;
}

qbVector<double> Ray::getPointB() const {
	return currPointB;
}