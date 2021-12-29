#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL.h>

class Image {
public:
	// Constructor
	Image();
	// Destructor
	~Image();

	// Functions
	void init(const int sizeX, const int sizeY, SDL_Renderer* currRenderer);
	void setPixel(const int x, const int y, const double r, const double g, const double b);
	void handleDisplay();

private:
	Uint32 convertColour(const double r, const double g, const double b);
	void initTex();

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