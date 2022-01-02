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
	int windowWidth = 640;
	int windowHeight = 360;
	currWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	// Create the current renderer
	if (currWindow != NULL) {
		currRenderer = SDL_CreateRenderer(currWindow, -1, 0);

		// Init Image Instance
		currImage.init(windowWidth, windowHeight, currRenderer);

		// Set BG Col to white
		SDL_SetRenderDrawColor(currRenderer, 255, 255, 255, 255);
		SDL_RenderClear(currRenderer);

		// Render scene
		currScene.render(currImage);

		// Display scene
		currImage.handleDisplay();
		SDL_RenderPresent(currRenderer);
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
	/*
	// Set BG Col
	SDL_SetRenderDrawColor(currRenderer, 255, 255, 255, 255);
	SDL_RenderClear(currRenderer);

	// Render scene
	currScene.render(currImage);

	// Display image tex
	currImage.handleDisplay();

	// Draw screen
	SDL_RenderPresent(currRenderer);
	*/
}

void CApp::onExit() {
	// Clean up structures
	SDL_DestroyRenderer(currRenderer);
	SDL_DestroyWindow(currWindow);
	currWindow = NULL;
	SDL_Quit();
}

// Debug printing for geometry
void CApp::printVector(const qbVector<double>&inputVector) {
	int numRows = inputVector.GetNumDims();
	for (int row = 0; row < numRows; row++) {
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}