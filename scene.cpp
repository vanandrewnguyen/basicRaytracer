#include "scene.h"

Scene::Scene() {
	// Set parameters
	currCamera.setPos(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
	currCamera.setLookat(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
	currCamera.setUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
	currCamera.setHorSize(0.25);
	currCamera.setAspect(16.0 / 9.0);
	currCamera.updateCameraGeometry();
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

			// Test intersection
			bool isIntersect = testSphere.testIntersection(cameraRay, intersectPoint, localNormal, localColour);

			// Output pixel colour 
			if (isIntersect) {	
				double dist = (intersectPoint - cameraRay.currPointA).norm();
				// Clamp distance
				if (dist > maxDist) {
					maxDist = dist;
				}
				if (dist < minDist) {
					minDist = dist;
				}
				outputImage.setPixel(x, y, 255.0 - ((dist - 9.0) / 0.94605) * 255.0, 0.0, 0.0);
			} else {
				outputImage.setPixel(x, y, 0.0, 0.0, 0.0);
			}
		}
	}

	std::cout << "Minimum distance: " << minDist << std::endl;
	std::cout << "Maximum distance: " << maxDist << std::endl;

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