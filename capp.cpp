#pragma once
#include "capp.h"

// Construct Class
CApp::CApp() {
	isRunning = true;
	currWindow = NULL;
	currRenderer = NULL;
}

// Init
bool CApp::onInit() {
	// Error Checking
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	// Create the current window
	const char* windowName = "Simple Raytracer";
	int windowWidth = 1280;
	int windowHeight = 720;
	currWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	// Create the current renderer
	if (currWindow != NULL) {
		currRenderer = SDL_CreateRenderer(currWindow, -1, 0);

		// Init Image Instance
		currImage.init(windowWidth, windowHeight, currRenderer);

		// Colour Variations (Debugging)
		for (int x = 0; x < windowWidth; ++x) {
			for (int y = 0; y < windowHeight; ++y) {
				double red = (static_cast<double>(x) / windowWidth) * 255.0;
				double green = (static_cast<double>(y) / windowHeight) * 255.0;
				currImage.setPixel(x, y, red, green, 0.0);
			}
		}
	} else {
		return false;
	}

	return true;
}

// Execution of SDL events
int CApp::onExecute() {
	SDL_Event event;
	if (!onInit()) {
		return -1;
	} 
	while (isRunning) {
		// While the window is running, it will execute any events called by SDL
		while (SDL_PollEvent(&event) != 0) {
			onEvent(&event);
		}
		onLoop();
		onRender();
	}
}

// Is called when an event is called
void CApp::onEvent(SDL_Event *event) {
	// Can add more SDL events but main one is for program to stop running
	if (event->type == SDL_QUIT) {
		isRunning = false;
	}
}

void CApp::onLoop() {

}

void CApp::onRender() {
	// Set BG Col
	SDL_SetRenderDrawColor(currRenderer, 255, 255, 255, 255);
	SDL_RenderClear(currRenderer);

	// Display image tex
	currImage.handleDisplay();

	// Draw screen
	SDL_RenderPresent(currRenderer);
}

void CApp::onExit() {
	// Clean up structures
	SDL_DestroyRenderer(currRenderer);
	SDL_DestroyWindow(currWindow);
	currWindow = NULL;
	SDL_Quit();
}