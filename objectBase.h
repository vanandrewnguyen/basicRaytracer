#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <memory>
#include "qbLinAlg/qbVector.h"
#include "ray.h"
#include "geometricTransform.h"

// Declare material base class, which will be overriden
class MaterialBase;

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
	void setTransformMatrix(const GeometricTransform &inputTransformMatrix);
	bool assignMaterial(const std::shared_ptr<MaterialBase> &inputObjectMaterial);

public:
	qbVector<double> baseColour{ 3 };
	GeometricTransform transformMatrix;
	std::shared_ptr<MaterialBase> objectMaterial;
	bool hasMaterial = false;
	qbVector<double> uvCoords{ 2 };
};

#endif