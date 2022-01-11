#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "materialBase.h"

class SimpleMaterial : public MaterialBase {
public:
	SimpleMaterial();
	virtual ~SimpleMaterial() override;

	// Functions
	virtual qbVector<double> computeColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
		const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& cameraRay);
	qbVector<double> computeSpecularColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const qbVector<double>& intersectionPoint, 
		const qbVector<double>& localNormal, const Ray& cameraRay);

public:
	qbVector<double> baseColour{ std::vector<double> {1.0, 0.0, 1.0} };
	double reflectivity = 0.0;
	double shininess = 0.0;
};



#endif