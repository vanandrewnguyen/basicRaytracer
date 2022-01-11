#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "image.h"
#include "camera.h"
#include "objectSphere.h"
#include "pointLight.h"
#include "objectPlane.h"

class Scene {
public:
	Scene();

	// Functions
	bool render(Image& outputImage);	
	bool castRay(Ray &castRay, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntersectionPoint, 
		qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColour);

private:
	// Functions

private:
	// Members
	Camera currCamera;

	// List of objects in the scene (ptr to base class, vector acts as list)
	std::vector<std::shared_ptr<ObjectBase>> objectList;

	// List of lights in the scene
	std::vector<std::shared_ptr<LightBase>> lightList;
};

#endif