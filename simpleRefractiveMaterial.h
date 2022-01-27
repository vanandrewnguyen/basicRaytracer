#ifndef SIMPLEREFRACTIVEMAT_H
#define SIMPLEREFRACTIVEMAT_H

#include "materialBase.h"

class SimpleRefractiveMaterial : public MaterialBase {
public:
	// Constructor destructor
	SimpleRefractiveMaterial();
	virtual ~SimpleRefractiveMaterial() override;

	// Functions
	virtual qbVector<double> computeColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
		const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& cameraRay) override;
	qbVector<double> computeSpecularColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const qbVector<double>& intersectionPoint,
		const qbVector<double>& localNormal, const Ray& cameraRay);
	qbVector<double> computeTranslucency(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
		const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& incidentRay);


public:
	qbVector<double> baseColour{ std::vector<double> {1.0, 0.0, 1.0} };
	double reflectivity = 0.0;
	double shininess = 0.0;
	double translucency = 0.0;
	double IOR = 1.0;
};

#endif