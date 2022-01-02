#ifndef OBJECTSPHERE_H
#define OBJECTSPHERE_H

#include "objectBase.h"

// This class inherits from Object Base
class ObjectSphere : public ObjectBase {
public:
	// Default constructor creates a unit sphere at the origin
	ObjectSphere();
	virtual ~ObjectSphere() override;

	// Functions
	virtual bool testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
		qbVector<double>& localNormal, qbVector<double>& localColour);

private:

};

#endif