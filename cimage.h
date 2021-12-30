#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL.h>

/*
Linking error if we put the functions in cimage.cpp, for some reason it does not link properly.
So it's pretty bad that we're pasting that code in a header file below but hey it works for now, I'll fix it later.
Usually LNK2019 occurs when you define a function in .h but don't actually write it in .cpp, but in my case all functions were defined.
So the problem could be that the file wasn't included in the build for whatever reason.
*/

class Image {
public:
	// Constructor
	Image() {
		screenSizeX = 0;
		screenSizeY = 0;
		screenTexture = NULL;
		screenRenderer = NULL;
	}
	// Destructor
	~Image() {
		// Clean up
		if (screenTexture != NULL) {
			SDL_DestroyTexture(screenTexture);
		}
	}

	// Functions
	void init(const int sizeX, const int sizeY, SDL_Renderer* currRenderer) {
		// Resize image array
		screenRChannel.resize(sizeX, std::vector<double>(sizeY, 0.0));
		screenGChannel.resize(sizeX, std::vector<double>(sizeY, 0.0));
		screenBChannel.resize(sizeX, std::vector<double>(sizeY, 0.0));

		// Store dimensions
		screenSizeX = sizeX;
		screenSizeY = sizeY;

		// Store reference to renderer
		screenRenderer = currRenderer;

		initTex();
	}
	void setPixel(const int x, const int y, const double r, const double g, const double b) {
		// Set pixel colour
		screenRChannel.at(x).at(y) = r;
		screenGChannel.at(x).at(y) = g;
		screenBChannel.at(x).at(y) = b;
	}
	void handleDisplay() {
		// Allocate mem for pixel buffer
		Uint32* tempPixelBuffer = new Uint32[screenSizeX * screenSizeY];
		// Clear
		memset(tempPixelBuffer, 0, screenSizeX * screenSizeY * sizeof(Uint32));

		// Loop through vector channels and then generate uint32 for each pixel
		for (int x = 0; x < screenSizeX; ++x) {
			for (int y = 0; y < screenSizeY; ++y) {
				// Convert x y loop into a linear index
				tempPixelBuffer[x + (y * screenSizeX)] = convertColour(screenRChannel.at(x).at(y),
					screenGChannel.at(x).at(y),
					screenBChannel.at(x).at(y));

			}
		}

		// Update texture with buffer
		SDL_UpdateTexture(screenTexture, NULL, tempPixelBuffer, screenSizeX * sizeof(Uint32));

		// Clean up (delete[] vs delete... delete[] deletes arrays, delete removes non-array objects)
		delete[] tempPixelBuffer;

		// Copy tex to renderer
		SDL_Rect srcRect, bounds;
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = screenSizeX;
		srcRect.h = screenSizeY;
		bounds = srcRect;
		SDL_RenderCopy(screenRenderer, screenTexture, &srcRect, &bounds);
	}

private:
	Uint32 convertColour(const double r, const double g, const double b) {
		// Type cast to convert data types
		unsigned char red = static_cast<unsigned char>(r);
		unsigned char green = static_cast<unsigned char>(g);
		unsigned char blue = static_cast<unsigned char>(b);

		Uint32 pixelColour;
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			pixelColour = (blue << 24) + (green << 16) + (red << 8) + 255;
		#else
			pixelColour = (255 << 24) + (red << 16) + (green << 8) + blue;
		#endif

		return pixelColour;
	}
	void initTex() {
		// Init rgba masks
		Uint32 rMask, gMask, bMask, aMask;

		// Compiler directive, see whether the user processer uses a big/little endian byte order (differs from system to system)
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
		#else
			rMask = 0x000000ff;
			gMask = 0x0000ff00;
			bMask = 0x00ff0000;
			aMask = 0xff000000;
		#endif

		// Delete previously created tex
		if (screenTexture != NULL) {
			SDL_DestroyTexture(screenTexture);
		}

		// Create tex that stores image
		SDL_Surface* tempSurf = SDL_CreateRGBSurface(0, screenSizeX, screenSizeY, 32, rMask, gMask, bMask, aMask);
		screenTexture = SDL_CreateTextureFromSurface(screenRenderer, tempSurf);
		SDL_FreeSurface(tempSurf);
	}

private:
	// Init vector of vectors of doubles for rgb channels (2d array to store data)
	// We are using Uint32 for each pixel, because we assign 32 bits of data per pixel
	std::vector<std::vector<double>> screenRChannel;
	std::vector<std::vector<double>> screenGChannel;
	std::vector<std::vector<double>> screenBChannel;

	// Store dimension of image
	int screenSizeX, screenSizeY;

	// SDL2
	SDL_Renderer* screenRenderer;
	SDL_Texture* screenTexture;
};

#endif