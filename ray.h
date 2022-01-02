#ifndef RAY_H
#define RAY_H
 
// Include Library from https://github.com/QuantitativeBytes/qbLinAlg
// Linear Algebra library by Michael Bennett
#include "qbLinAlg/qbVector.h"

class Ray {
public:
	// Constructor
	Ray(const qbVector<double> &pointA, const qbVector<double> &pointB);

	qbVector<double> getPointA() const;
	qbVector<double> getPointB() const;

public:
	// Public Functions (keep elements and functions seperate)
	qbVector<double> currPointA {3};
	qbVector<double> currPointB {3};
	qbVector<double> currVecAB {3};
};


#endif