// Ifndef is used so that the compiler only calls these once
#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>
#include "image.h"
#include "scene.h"
#include "camera.h"
#include "textureSimplex.h"

class CApp {
public:
	// Constructor
	CApp();

	// Functions
	int onExecute();
	bool onInit();
	void onEvent(SDL_Event* event);
	void onLoop();
	void onRender();
	void onExit(); 

private:
	void printVector(const qbVector<double>& inputVector);

private:
	// Instance of Image class to store an image
	Image currImage;

	// Instance of Scene class
	Scene currScene;

	// SDL2 Variables
	bool isRunning;
	SDL_Window* currWindow;
	SDL_Renderer* currRenderer;
};


#endif