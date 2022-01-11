#include "materialBase.h"

MaterialBase::MaterialBase() {

}

MaterialBase::~MaterialBase() {

}

// Functions
qbVector<double> MaterialBase::computeColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
	const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const Ray& cameraRay) {
	// Define initial material colour
	qbVector<double> matColour{ 3 };

	return matColour;
}

qbVector<double> MaterialBase::computeDiffuseColour(const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::vector<std::shared_ptr<LightBase>>& lightList, const std::shared_ptr<ObjectBase>& currentObject,
	const qbVector<double>& intersectionPoint, const qbVector<double>& localNormal, const qbVector<double>& baseColour) {
	// Compute colour based on diffuse illumination
	qbVector<double> difCol{ 3 };
	double intensity;
	qbVector<double> colour{ 3 };
	double outputRed = 0.0;
	double outputGreen = 0.0;
	double outputBlue = 0.0;
	bool validLight = false;
	bool lightFound = false;

	// For every light add to rgb values on the screen
	for (auto currentLight : lightList) {
		validLight = currentLight->computeIlluminationContribution(intersectionPoint, localNormal, objectList, currentObject, colour, intensity);
		if (validLight) {
			lightFound = true;
			outputRed += colour.GetElement(0) * intensity;
			outputGreen += colour.GetElement(1) * intensity;
			outputBlue += colour.GetElement(2) * intensity;
		}
	}

	// Merge output intensity with object colour
	if (lightFound) {
		difCol.SetElement(0, outputRed * baseColour.GetElement(0));
		difCol.SetElement(1, outputGreen * baseColour.GetElement(1));
		difCol.SetElement(2, outputBlue * baseColour.GetElement(2));
	}
	
	// Return mat col
	return difCol;
}

bool MaterialBase::castRay(const Ray& castRay, const std::vector<std::shared_ptr<ObjectBase>>& objectList,
	const std::shared_ptr<ObjectBase>& thisObject, std::shared_ptr<ObjectBase>& closestObject, qbVector<double>& closestIntersectionPoint,
	qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColour) {
	qbVector<double> intersectionPoint{ 3 };
	qbVector<double> localNormal{ 3 };
	qbVector<double> localColour{ 3 };
	double minDist = 1e6;
	bool intersectionFound = false;

	for (auto currentObject : objectList) {
		bool isIntersect = currentObject->testIntersection(castRay, intersectionPoint, localNormal, localColour);
		// Output pixel colour 
		if (isIntersect) {
			// Set flag to show we found an intersection
			intersectionFound = true;

			// Compute distance between camera and point of intersection
			double dist = (closestIntersectionPoint - castRay.currPointA).norm(); // measure the distance, if it is less than any other then we keep reference

			// If this object is closer to the camera, store a reference 
			if (dist < minDist) {
				minDist = dist;
				closestObject = currentObject;
				closestIntersectionPoint = intersectionPoint;
				closestLocalNormal = localNormal;
				closestLocalColour = localColour;
			}
		}
	}
	return intersectionFound;
}
