#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "objectBase.h"
#include "lightBase.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"

class MaterialBase {
public:
	// Constructor Destructor
	MaterialBase();
	virtual ~MaterialBase();

	// Functions
	virtual qbVector<double> computeColour(const std::vector<std::shared_ptr<ObjectBase>> &objectList, 
		const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase> &currentObject,
		const qbVector<double> &intersectionPoint, const qbVector<double> &localNormal, const Ray &cameraRay);
	static qbVector<double> computeDiffuseColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
		const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const qbVector<double> &baseColour);
	bool castRay(const Ray &castRay, const std::vector<std::shared_ptr<ObjectBase>> &objectList, 
		const std::shared_ptr<ObjectBase> &thisObject, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntersectionPoint,
		qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColour);

public:
	

};


#endif