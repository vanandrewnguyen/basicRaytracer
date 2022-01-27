#include "simpleRefractiveMaterial.h"

#define SURFDIS 0.001

SimpleRefractiveMaterial::SimpleRefractiveMaterial() {

}

SimpleRefractiveMaterial::~SimpleRefractiveMaterial() {

}

qbVector<double> SimpleRefractiveMaterial::computeColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
	const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& cameraRay) {
	// Define initial material colours
	qbVector<double> matColour{ 3 };
	qbVector<double> refColour{ 3 };
	qbVector<double> difColour{ 3 };
	qbVector<double> specColour{ 3 };
	qbVector<double> translucentColour{ 3 };

	// Compute diffuse component
	if (!hasTexture) {
		difColour = computeDiffuseColour(objectList, lightList, currentObject, intersectionPoint, localNormal, baseColour);
	} else {
		difColour = computeDiffuseColour(objectList, lightList, currentObject, intersectionPoint, localNormal, 
		textureList.at(0)->getColourAtUVCoord(currentObject->uvCoords));
	}

	// Compute reflection component
	if (reflectivity > 0.0) {
		refColour = computeReflectionColour(objectList, lightList, currentObject, intersectionPoint, localNormal, cameraRay);
	}

	// Combine reflection and diffuse
	matColour = (refColour * reflectivity) + (difColour * (1.0 - reflectivity));

	// Compute refractive component
	if (translucency > 0.0) {
		translucentColour = computeTranslucency(objectList, lightList, currentObject, intersectionPoint, localNormal, cameraRay);
	}

	// Combine
	matColour = (translucentColour * translucency) + (matColour * (1.0 - translucency));

	// Compute specular
	if (shininess > 0.0) {
		specColour = computeSpecularColour(objectList, lightList, intersectionPoint, localNormal, cameraRay);
	}

	// Combine again
	matColour = matColour + specColour;
	return matColour;
}

qbVector<double> SimpleRefractiveMaterial::computeSpecularColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const qbVector<double>& intersectionPoint,
	const qbVector<double>& localNormal, const Ray& cameraRay) {
	
	/* IDENTICAL TO SIMPLEMATERIAL.H */
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

qbVector<double> SimpleRefractiveMaterial::computeTranslucency(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
	const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& incidentRay) {
	qbVector<double> translucencyColour{ 3 };

	// Compute refracted vector
	qbVector<double> p = incidentRay.currVecAB;
	p.Normalize();
	qbVector<double> tempNormal = localNormal;
	double r = 1.0 / IOR;
	double c = -qbVector<double>::dot(tempNormal, p);
	if (c < 0.0) {
		tempNormal = tempNormal * -1.0; // force it to be positive
		c = -qbVector<double>::dot(tempNormal, p);
	}

	// Check incident ray equation
	qbVector<double> refractedVector = r * p + (r * c - sqrtf(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)))) * tempNormal;

	// Construct refracted ray
	Ray refractedRay(intersectionPoint + (refractedVector * 0.01), intersectionPoint + refractedVector);

	// Test 2nd intersection (intersect with exiting side of object)
	std::shared_ptr<ObjectBase> closestObject;
	qbVector<double> closestIntersectPoint{ 3 };
	qbVector<double> closestLocalNormal{ 3 };
	qbVector<double> closestLocalColour{ 3 };
	qbVector<double> newIntersectPoint{ 3 };
	qbVector<double> newLocalNormal{ 3 };
	qbVector<double> newLocalColour{ 3 };

	bool test = currentObject->testIntersection(refractedRay, newIntersectPoint, newLocalNormal, newLocalColour);
	bool foundInt = false;
	Ray exitingRay;

	if (test) {
		// Ray has exited the object
		qbVector<double> p2 = refractedRay.currVecAB; // identical to above
		p2.Normalize();
		qbVector<double> tempNormal2 = newLocalNormal;
		double r2 = IOR;
		double c2 = -qbVector<double>::dot(tempNormal2, p2);
		
		if (c2 < 0.0) {
			tempNormal2 = tempNormal2 * -1.0;
			c2 = -qbVector<double>::dot(tempNormal2, p2);
		}

		qbVector<double> exitingVector = r2 * p2 + (r2 * c2 - sqrtf(1.0 - pow(r2, 2.0) * (.10 - pow(c2, 2.0)))) * tempNormal2;

		// Compute refracted ray
		Ray refractedRay2(newIntersectPoint + (exitingVector * 0.01), newIntersectPoint + exitingVector);

		// Cast this ray into the scene, leaving the object and finding a colour to sample
		foundInt = castRay(refractedRay2, objectList, currentObject, closestObject, closestIntersectPoint, closestLocalNormal, closestLocalColour);
		exitingRay = refractedRay2;
	} else {
		// No secondary intersection foud, so continue original refracted ray
		foundInt = castRay(refractedRay, objectList, currentObject, closestObject, closestIntersectPoint, closestLocalNormal, closestLocalColour);
		exitingRay = refractedRay;
	}

	// Compute colour for closest object
	qbVector<double> matCol{ 3 };
	if (foundInt) {
		if (closestObject->hasMaterial) {
			matCol = closestObject->objectMaterial->computeColour(objectList, lightList, closestObject, closestIntersectPoint, closestLocalNormal, exitingRay);
		} else {
			matCol = MaterialBase::computeDiffuseColour(objectList, lightList, closestObject, closestIntersectPoint, closestLocalNormal, closestObject->baseColour);
		}
	} else {
		// No intersection found, leave mat col as is
	}

	translucencyColour = matCol;
	return translucencyColour;
}
