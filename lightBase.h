#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "qbLinAlg/qbVector.h"
#include "ray.h"
#include "objectBase.h"

class LightBase {
public:
	LightBase();
	virtual ~LightBase();

	// Functions
	virtual bool computeIlluminationContribution(const qbVector<double>& intersectPoint, const qbVector<double>& localNormal,
		const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject,
		qbVector<double>& colour, double& intensity);

public:
	qbVector<double> lightColour{ 3 };
	qbVector<double> lightLocation{ 3 };
	double lightIntensity;
};


#endif
