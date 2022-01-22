#ifndef OBJECTCUBE_H
#define OBJECTCUBE_H

#include "objectBase.h"
#include "geometricTransform.h"

class ObjectCube : public ObjectBase {
	// Constructor destructor
	ObjectCube();
	virtual ~ObjectCube() override;

	// Functions
	virtual bool testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
		qbVector<double>& localNormal, qbVector<double>& localColour) override;
};

#endif