#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <SDL.h>
#include "image.h"
#include "camera.h"
#include "objectSphere.h"

class Scene {
public:
	Scene();

	// Functions
	bool render(Image& outputImage);	

private:
	// Functions

private:
	// Members
	Camera currCamera;

	// Unit sphere test
	ObjectSphere testSphere;
};

#endif