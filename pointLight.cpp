#include "pointLight.h"
#define PI 3.1416

PointLight::PointLight() {
	lightColour = qbVector<double>{ std::vector<double> {1.0, 1.0, 1.0} };
	lightIntensity = 1.0;
}
PointLight::~PointLight() {

}

bool PointLight::computeIlluminationContribution(const qbVector<double>& intersectPoint, const qbVector<double>& localNormal,
	const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject,
	qbVector<double>& colour, double& intensity) {
	/*
	Aim is to use the dot product to get the angle between the normal vector and the vector of intersection (from light source)
	This gives us an indication of how much light should be hitting the surface, i.e. if the vectors are parallel (angle is 0),
	then the light should be at its strongest. Whereas if the light is hitting a perpendicular angle (dot = 0, cos = PI/2), 
	there will be no light on that surface.
	*/
	// Construct vector moving away from intersection point
	qbVector<double> lightDir = (lightLocation - intersectPoint).Normalized();
	double lightDist = (lightLocation - intersectPoint).norm();

	// Compute start
	qbVector<double> pointStart = intersectPoint;
	
	// Construct a ray from point of intersection to the light
	Ray lightRay(pointStart, pointStart + lightDir);

	// Check for intersections with all of the objects in scene, except for current one
	qbVector<double> pointOfIntersection{ 3 };
	qbVector<double> pointOfIntersectionNormal{ 3 };
	qbVector<double> pointOfIntersectionColour{ 3 };
	bool validInt = false;
	for (auto sceneObject : objectList) {
		if (sceneObject != currentObject) {
			validInt = sceneObject->testIntersection(lightRay, pointOfIntersection, pointOfIntersectionNormal, pointOfIntersectionColour);
			// If distance to current object and poi of object tested lies between current obj and light, cast shadow. Else forget it.
			if (validInt) {
				double dist = (pointOfIntersection - pointStart).norm();
				if (dist > lightDist) {
					validInt = false;
				}
			}
		}
		// If we have a valid intersection, break. Since the object is blocking light.
		if (validInt) {
			break;
		}
	}

	// Continue computing if light ray did not intersection with any objects
	if (!validInt) {
		// Compute angle between surface normal and light vector
		// Assume normal is a unit vector
		double angle = acos(qbVector<double>::dot(localNormal, lightDir));
		if (angle > PI / 2.0) {
			// No light reaches since normal is pointing away from light source
			colour = lightColour;
			intensity = 0.0;
			return false;
		}
		else {
			// Compute light
			colour = lightColour;
			intensity = lightIntensity * (1.0 - (angle / (PI / 2.0)));
			return true;
		}
	} else {
		// We are in shadow
		colour = lightColour;
		intensity = 0.0;
		return false;
	}

	return true;
}

/*
	// Compute angle between surface normal and light vector
	// Assume normal is a unit vector
	double angle = acos(qbVector<double>::dot(localNormal, lightDir));
	if (angle > PI / 2.0) {
		// No light
		colour = lightColour;
		intensity = 0.0;
		return false;
	} else {
		// Compute light
		colour = lightColour;
		intensity = lightIntensity * (1.0 - (angle / (PI / 2.0)));
		return true;
	}
*/