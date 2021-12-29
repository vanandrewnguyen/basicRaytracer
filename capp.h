// Ifndef is used so that the compiler only calls these once
#ifndef CAPP_H
#define CAPP_H

#include<SDL.h>

class CApp {
public:
	// Constructor
	CApp();

	int onExecute();
	bool onInit();
	void onEvent(SDL_Event* event);
	void onLoop();
	void onRender();
	void onExit();

private:
	// SDL2 Variables
	bool isRunning;
	SDL_Window* currWindow;
	SDL_Renderer* currRenderer;
};


#endif