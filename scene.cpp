#include "scene.h"

Scene::Scene() {
	// CAMERA //
	// Set parameters
	currCamera.setPos(qbVector<double>{std::vector<double>{0.0, -10.0, -1.0}});
	currCamera.setLookat(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
	currCamera.setUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
	currCamera.setHorSize(0.25);
	currCamera.setAspect(16.0 / 9.0);
	currCamera.updateCameraGeometry();

	// CONSTRUCTION //
	// Construct sphere (push back into list)
	objectList.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));
	objectList.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));
	objectList.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));

	// Construct plane
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));

	// TRANSFORMATIONS //
	// Modify each sphere (using geometric transforms - translation, rotation, scaling)
	GeometricTransform matrix1, matrix2, matrix3, matrix4;
	
	matrix1.setTransform(qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}}, 
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});
	matrix2.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
	matrix3.setTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});
	matrix4.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.75}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});

	objectList.at(0)->setTransformMatrix(matrix1);
	objectList.at(1)->setTransformMatrix(matrix2);
	objectList.at(2)->setTransformMatrix(matrix3);
	objectList.at(3)->setTransformMatrix(matrix4);

	// COLOURS //
	objectList.at(0)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(1)->baseColour = qbVector<double>{ std::vector<double>{0.2, 0.8, 1.0} };
	objectList.at(2)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.0} };
	objectList.at(3)->baseColour = qbVector<double>{ std::vector<double>{0.5, 0.5, 0.5} };

	// LIGHTING //
	// Construct point light
	lightList.push_back(std::make_shared<PointLight>(PointLight()));
	// Move point light off the origin, and set colour
	lightList.at(0)->lightLocation = qbVector<double>{ std::vector<double>{5.0, -10.0, -5.0} };
	lightList.at(0)->lightColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };

}

// Render function
bool Scene::render(Image& outputImage) {
	// Get dimensions of output image
	int sizeX = outputImage.getSizeX();
	int sizeY = outputImage.getSizeY();

	// Ray-tracing algorithm
	// Loop over each pixel in our image.
	Ray cameraRay;
	qbVector<double> intersectPoint{ 3 };
	qbVector<double> localNormal{ 3 };
	qbVector<double> localColour{ 3 };
	double xScalingFactor = 1.0 / (static_cast<double>(sizeX) / 2.0);
	double yScalingFactor = 1.0 / (static_cast<double>(sizeY) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {
			// Normalise XY Coord
			double normX = (static_cast<double>(x) * xScalingFactor) - 1.0; // -1 -> 1
			double normY = (static_cast<double>(y) * yScalingFactor) - 1.0;

			// Generate ray
			currCamera.createRay(normX, normY, cameraRay);

			// Test for intersections with all objects in the scene (using loop, auto is meant to define the correct data type)
			std::shared_ptr<ObjectBase> closestObject;
			qbVector<double> closestIntersectionPoint{ 3 };
			qbVector<double>closestLocalNormal{ 3 };
			qbVector<double>closestLocalColour{ 3 };
			double minDist = 1e6;
			bool intersectionFound = false;
			
			for (auto currentObject : objectList) {
				bool isIntersect = currentObject->testIntersection(cameraRay, intersectPoint, localNormal, localColour);
				// Output pixel colour 
				if (isIntersect) {
					// Set flag to show we found an intersection
					intersectionFound = true;

					// Compute distance between camera and point of intersection
					double dist = (intersectPoint - cameraRay.currPointA).norm(); // measure the distance, if it is less than any other then we keep reference
					
					// If this object is closer to the camera, store a reference 
					if (dist < minDist) {
						minDist = dist;
						closestObject = currentObject;
						closestIntersectionPoint = intersectPoint;
						closestLocalNormal = localNormal;
						closestLocalColour = localColour;
					}
				}
			}

			// Compute lighting for closest object
			if (intersectionFound) {
				// Compute intensity
				double intensity;
				qbVector<double> colour{ 3 };
				double red = 0.0;
				double green = 0.0;
				double blue = 0.0;
				bool validLight = false;
				bool lightFound = false;

				// For every light add to rgb values on the screen
				for (auto currentLight : lightList) {
					validLight = currentLight->computeIlluminationContribution(closestIntersectionPoint, closestLocalNormal, objectList, closestObject,
						colour, intensity);
					if (validLight) {
						lightFound = true;
						red += colour.GetElement(0) * intensity;
						green += colour.GetElement(1) * intensity;
						blue += colour.GetElement(2) * intensity;
					}
				}

				// Merge output intensity with object colour
				if (lightFound) {
					red *= closestLocalColour.GetElement(0);
					green *= closestLocalColour.GetElement(1);
					blue *= closestLocalColour.GetElement(2);
					// Output
					outputImage.setPixel(x, y, red, green, blue);
				}
			}
		}
	}
	return true;
}
