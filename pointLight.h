#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightBase.h"

// Child of the base light class
class PointLight : public LightBase {
public:
	PointLight();
	virtual ~PointLight() override;

	virtual bool computeIlluminationContribution(const qbVector<double>& intersectPoint, const qbVector<double>& localNormal,
		const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject,
		qbVector<double>& colour, double& intensity) override;
};


#endif