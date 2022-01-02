#include "scene.h"

Scene::Scene() {

}

// Render function
bool Scene::render(Image& outputImage) {
	// Get dimensions of output image
	int sizeX = outputImage.getSizeX();
	int sizeY = outputImage.getSizeY();

	// Create colour gradient
	for (int x = 0; x < sizeX; ++x) {
		for (int y = 0; y < sizeY; ++y) {
			double red = (static_cast<double>(x) / sizeX) * 255.0;
			double green = (static_cast<double>(y) / sizeY) * 255.0;
			outputImage.setPixel(x, y, red, green, 0.0);
		}
	}

	return true;
}