// Ifndef is used so that the compiler only calls these once
#ifndef CAPP_H
#define CAPP_H

#include "cimage.h"
#include <SDL.h>


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
	// Instance of Image class to store an image
	Image currImage;

	// SDL2 Variables
	bool isRunning;
	SDL_Window* currWindow;
	SDL_Renderer* currRenderer;
};


#endif