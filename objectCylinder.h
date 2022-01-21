#ifndef OBJECTCYLINDER_H
#define OBJECTCYLINDER_H

#include "objectBase.h"
#include "geometricTransform.h"

class ObjectCylinder : public ObjectBase {
public:
	// Constructor destructor
	ObjectCylinder();
	virtual ~ObjectCylinder() override;

	// Functions
	virtual bool testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
		qbVector<double>& localNormal, qbVector<double>& localColour) override;
};

#endif