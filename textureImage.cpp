#include "textureImage.h"

Texture::TextureImage::TextureImage() {

}

Texture::TextureImage::~TextureImage() {
	// Clean up image
	if (isImageLoaded) {
		// Free
		SDL_FreeSurface(imageSurf);
		isImageLoaded = false;
	}
}

qbVector<double> Texture::TextureImage::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	qbVector<double> output{ 4 };
	if (!isImageLoaded) {
		// Default will be bright red if no image loaded
		output = qbVector<double>{ std::vector<double>{1.0, 0.0, 0.0, 1.0} };
	} else {
		qbVector<double> inputLocation = uvCoords;
		qbVector<double> newLocation = applyTransform(inputLocation);
		double u = newLocation.GetElement(0);
		double v = newLocation.GetElement(1);

		// Convert (u, v) to image dimensions (x, y)
		// u and v go from -1->1 so we just convert that to 0->1 range by +1 / 2
		int x = static_cast<int>(round(((u + 1.0) / 2.0) * static_cast<double>(sizeX)));
		int y = sizeY - (static_cast<int>(round(((v + 1.0) / 2.0) * static_cast<double>(sizeY))));

		// Modulo for tiling
		x = ((x % sizeX) + sizeX) % sizeX; // mod twice for negative nums
		y = ((y % sizeY) + sizeY) % sizeY;

		// If we are in the image...
		if ((x >= 0) && (x < sizeX) && (y >= 0) && (y < sizeY)) {
			// Convert xy to linear index
			int pixelIndex = x + (y * (pitch / bytesPerPixel)); // pixel array for sdl surf
			uint32_t* pixels = (uint32_t*)imageSurf->pixels;
			uint32_t currPixel = pixels[pixelIndex];
			uint8_t r, g, b, a;
			SDL_GetRGBA(currPixel, imageSurf->format, &r, &g, &b, &a);

			// Set output vec
			output.SetElement(0, static_cast<double>(r) / 255.0);
			output.SetElement(1, static_cast<double>(g) / 255.0);
			output.SetElement(2, static_cast<double>(b) / 255.0);
			output.SetElement(3, static_cast<double>(a) / 255.0);
		}
	}

	return output;
}

bool Texture::TextureImage::loadImage(std::string fileName) {
	// If is loaded already, then free the existing surface
	if (isImageLoaded) {
		SDL_FreeSurface(imageSurf);
	}

	currFileName = fileName;
	imageSurf = SDL_LoadBMP(fileName.c_str()); // c_str returns a ptr to char array // sdl_loadbmp loads a bitmap image from file path
	if (!imageSurf) {
		// If we can't load it then chuck out an error msg
		std::cout << "Didn't load image: " << SDL_GetError() << std::endl;
		isImageLoaded = false;
		return isImageLoaded;
	}

	// Grab information from image
	sizeX = imageSurf->w;
	sizeY = imageSurf->h;
	pitch = imageSurf->pitch;
	pixelFormat = imageSurf->format;
	bytesPerPixel = pixelFormat->BytesPerPixel;
	rMask = pixelFormat->Rmask;
	gMask = pixelFormat->Gmask;
	bMask = pixelFormat->Bmask;
	aMask = pixelFormat->Amask;

	isImageLoaded = true;
	return isImageLoaded;
}