#ifndef OBJECTPLANE_H
#define OBJECTPLANE_H

#include "objectBase.h"
#include "geometricTransform.h"

class ObjectPlane : public ObjectBase {
public:
	// Constructor 
	ObjectPlane();

	// Override destructor
	virtual ~ObjectPlane() override;

	// Functions
	virtual bool testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
		qbVector<double>& localNormal, qbVector<double>& localColour) override;

private:

};


#endif