#include "ray.h"

// Default constructor vs defined constructor
Ray::Ray() {
	currPointA = qbVector<double>{ std::vector<double>{0.0, 0.0, 0.0} };
	currPointA = qbVector<double>{ std::vector<double>{0.0, 0.0, 0.0} };
	currVecAB = currPointB - currPointA;
}

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