#ifndef OBJECTCONE_H
#define OBJECTCONE_H

#include "objectBase.h"
#include "geometricTransform.h"

class ObjectCone : public ObjectBase {
public:
	// Constructor destructor
	ObjectCone();
	virtual ~ObjectCone() override;

	// Functions
	virtual bool testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
		qbVector<double>& localNormal, qbVector<double>& localColour) override;
};

#endif