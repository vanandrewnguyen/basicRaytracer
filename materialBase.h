#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "textureBase.h"
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
	qbVector<double> computeReflectionColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
		const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
		const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& incidentRay);
	void assignTexture(const std::shared_ptr<Texture::TextureBase>& inputTex);


public:
	// Counter for reflections
	inline static int maxReflRays; // inline static means one instance of each variable regardless of how many materialBase instances there are
	inline static int reflRayCount;

	// Ambient light
	inline static qbVector<double> ambientCol{ std::vector<double>{1.0, 1.0, 1.0} };
	inline static double ambientLightIntensity = 0.1;

	// Texture list
	std::vector<std::shared_ptr<Texture::TextureBase>> textureList; // can have multiple textures in a vector
	bool hasTexture = false;
};


#endif