#include "scene.h"

Scene::Scene() {
	// Set parameters
	currCamera.setPos(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
	currCamera.setLookat(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
	currCamera.setUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
	currCamera.setHorSize(0.25);
	currCamera.setAspect(16.0 / 9.0);
	currCamera.updateCameraGeometry();

	// Construct sphere (push back into list)
	objectList.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));
	objectList.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));
	objectList.push_back(std::make_shared<ObjectSphere> (ObjectSphere()));

	// Modify each sphere (using geometric transforms - translation, rotation, scaling)
	GeometricTransform matrix1, matrix2, matrix3;
	matrix1.setTransform(qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}}, 
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});
	matrix2.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});
	matrix3.setTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});
	objectList.at(0)->setTransformMatrix(matrix1);
	objectList.at(1)->setTransformMatrix(matrix2);
	objectList.at(2)->setTransformMatrix(matrix3);
	objectList.at(0)->baseColour = qbVector<double>{ std::vector<double>{255.0, 153.0, 153.0} };
	objectList.at(1)->baseColour = qbVector<double>{ std::vector<double>{51.0, 204.0, 255.0} };
	objectList.at(2)->baseColour = qbVector<double>{ std::vector<double>{255.0, 153.0, 0.0} };

	// Construct point light
	lightList.push_back(std::make_shared<PointLight>(PointLight()));
	// Move point light off the origin, and set colour
	lightList.at(0)->lightLocation = qbVector<double>{ std::vector<double>{5.0, -10.0, -5.0} };
	lightList.at(0)->lightColour = qbVector<double>{ std::vector<double>{255.0, 255.0, 255.0} };

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
			for (auto currentObject : objectList) {
				bool isIntersect = currentObject->testIntersection(cameraRay, intersectPoint, localNormal, localColour);
				// Output pixel colour 
				if (isIntersect) {
					// Compute intensity of light
					double intensity;
					bool validLight = false;
					qbVector<double> colour{ 3 };
					for (auto currentLight : lightList) {
						validLight = currentLight->computeIlluminationContribution(intersectPoint, localNormal, objectList, currentObject, 
							colour, intensity);
					}

					// Compute dist between camera and intersection point
					double dist = (intersectPoint - cameraRay.currPointA).norm();
					// Clamp distance
					if (dist > maxDist) {
						maxDist = dist;
					}
					if (dist < minDist) {
						minDist = dist;
					}

					// Display light
					//outputImage.setPixel(x, y, 255.0 - (((dist - 9.0) / 0.94605) * 255.0), 0.0, 0.0);
					if (validLight) {
						//outputImage.setPixel(x, y, 255.0 * intensity, 0.0, 0.0);
						outputImage.setPixel(x, y, localColour.GetElement(0) * intensity, localColour.GetElement(1) * intensity, localColour.GetElement(2) * intensity);
					} else {
						// Leave pixel unchanged
						//outputImage.setPixel(x, y, 0.0, 0.0, 0.0);
					}
				}
				else {
					// Leave pixel unchanged
					//outputImage.setPixel(x, y, 0.0, 0.0, 0.0);
				}
			}
		}
	}

	/*
	// Create colour gradient
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {
			double red = (static_cast<double>(x) / sizeX) * 255.0;
			double green = (static_cast<double>(y) / sizeY) * 255.0;
			outputImage.setPixel(x, y, red, green, 0.0);
		}
	}
	*/

	return true;
}