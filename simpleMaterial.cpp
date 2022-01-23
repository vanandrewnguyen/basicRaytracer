#include "simpleMaterial.h"

#define SURFDIS 0.001

SimpleMaterial::SimpleMaterial() {

}

SimpleMaterial::~SimpleMaterial() {

}

// Override from base class
qbVector<double> SimpleMaterial::computeColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
	const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& cameraRay) {
	// Initial material colours
	qbVector<double> matColour{ 3 };
	qbVector<double> reflColour{ 3 };
	qbVector<double> diffColour{ 3 };
	qbVector<double> specColour{ 3 };

	// Compute diffuse light
	if (!hasTexture) {
		diffColour = computeDiffuseColour(objectList, lightList, currentObject, intersectionPoint, localNormal, baseColour);
	} else {
		// Super cool reference here, use the tex vector to get first element and grab colour at a uv coord which is given by the current obj
		diffColour = computeDiffuseColour(objectList, lightList, currentObject, intersectionPoint, localNormal, 
		textureList.at(0)->getColourAtUVCoord(currentObject->uvCoords));
	}

	// Compute reflections!
	if (reflectivity > 0.0) {
		reflColour = computeReflectionColour(objectList, lightList, currentObject, intersectionPoint, localNormal, cameraRay);
	}

	// Combine reflection with diffuse -> the more reflective a material is, the more it loses its base colour
	matColour = (reflColour * reflectivity) + (diffColour * (1 - reflectivity));

	// Compute specular light
	if (shininess > 0.0) {
		specColour = computeSpecularColour(objectList, lightList, intersectionPoint, localNormal, cameraRay);
	}

	// Final output
	matColour = matColour + specColour; // spec doesn't need to be affected by reflections
	// also += doesn't work, qbVector overrides vector arithmetic 
	return matColour;
}

qbVector<double> SimpleMaterial::computeSpecularColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const qbVector<double>& intersectionPoint,
	const qbVector<double>& localNormal, const Ray& cameraRay) {
	qbVector<double> specColour{ 3 };
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;

	// Loop through lights in scene
	for (auto currLight : lightList) {
		// Check for intersections with objects in scene
		double intensity = 0.0;

		// Construct vector from intersectionPoint to light source
		qbVector<double> lightDir = (currLight->lightLocation - intersectionPoint).Normalized();

		// Compute start point
		qbVector<double> startPoint = intersectionPoint + (lightDir * SURFDIS); // move away from surface

		// Construct ray from point of intersection to light
		Ray lightRay(startPoint, startPoint + lightDir);

		// Loop through objects in scene and check if light is obstructed
		qbVector<double> pointOfIntersection{ 3 };
		qbVector<double> pointOfIntersectionNormal{ 3 };
		qbVector<double> pointOfIntersectionColour{ 3 };
		bool hasIntersection = false;
		for (auto currObject : objectList) {
			hasIntersection = (currObject->testIntersection(lightRay, pointOfIntersection, pointOfIntersectionNormal, pointOfIntersectionColour));
			if (hasIntersection) {
				break;
			}
		}

		// If no intersection then make spec component
		if (!hasIntersection) {
			qbVector<double> d = lightRay.currVecAB;
			qbVector<double> r = d - (2 * qbVector<double>::dot(d, localNormal) * localNormal); // check learnOpenGL
			r.Normalize();

			// Get dot prod
			qbVector<double> v = cameraRay.currVecAB;
			v.Normalize();
			double dotProd = qbVector<double>::dot(r, v);

			// Only continue if dot prod is positive
			if (dotProd > 0.0) {
				intensity = reflectivity * std::pow(dotProd, shininess);
			}
		}

		// Add to output
		red += currLight->lightColour.GetElement(0) * intensity;
		green += currLight->lightColour.GetElement(1) * intensity;
		blue += currLight->lightColour.GetElement(2) * intensity;
	}

	// Return output
	specColour.SetElement(0, red);
	specColour.SetElement(1, green);
	specColour.SetElement(2, blue);
	return specColour;
}

