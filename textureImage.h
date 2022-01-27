#ifndef TEXTUREIMAGE_H
#define TEXTUREIMAGE_H

#include "textureBase.h"
#include <SDL.h>

namespace Texture {
	class TextureImage : public TextureBase {
	public:
		// Constructor destructor
		TextureImage();
		virtual ~TextureImage() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		bool loadImage(std::string fileName);

	private:
		std::string currFileName;
		SDL_Surface* imageSurf;
		SDL_PixelFormat* pixelFormat;
		bool isImageLoaded = false;
		int sizeX, sizeY, pitch;
		uint8_t bytesPerPixel; // fixed width
		uint32_t rMask, gMask, bMask, aMask; // rgba mask (image.h)
	};
}

#endif

