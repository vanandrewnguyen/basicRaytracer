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

// Called per frame
void CApp::onLoop() {
	// Set BG Col
	SDL_SetRenderDrawColor(currRenderer, 255, 255, 255, 255);
	SDL_RenderClear(currRenderer);

	// Draw screen
	SDL_RenderPresent(currRenderer);
}

void CApp::onRender() {
	
}

void CApp::onExit() {
	// Clean up structures
	SDL_DestroyRenderer(currRenderer);
	SDL_DestroyWindow(currWindow);
	currWindow = NULL;
	SDL_Quit();
}