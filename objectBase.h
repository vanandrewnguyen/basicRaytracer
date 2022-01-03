#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "qbLinAlg/qbVector.h"
#include "ray.h"

// This is a base class of every 3D object, which will have elements that are inherited.
class ObjectBase {
public:
	// Constructor and destructor (declare as virtual because we intend to overwrite the destructor in child objects)
	ObjectBase();
	virtual ~ObjectBase();

	// Functions
	virtual bool testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
		qbVector<double>& localNormal, qbVector<double>& localColour);
	bool isFloatCloseEnough(const double n1, const double n2);

public:
	qbVector<double> baseColour{ 3 };
};

#endif