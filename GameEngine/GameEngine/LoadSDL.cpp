#include "LoadSDL.h"
#include <iostream>

using namespace std;

SDL_Renderer* LoadSDL::m_Renderer = nullptr;

// Function definition
LoadSDL::LoadSDL() {

}
LoadSDL::~LoadSDL() {

}
void LoadSDL::load() {
	//Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		cout << "Initialised SDL successfully! \n";

		// Created window for rendering with 1280W x 940H
		sdlWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 940, SDL_WINDOW_SHOWN);

		// Render for the created window
		m_Renderer = SDL_CreateRenderer(sdlWindow, 0, -1);
		if (m_Renderer != nullptr) {
			cout << "Create renderer successful!!! \n";
		}

		// Validate loading of font
		if (TTF_Init() == -1) {
			cerr << "failed to initialise TTF. \n";
		}
	}
}

void LoadSDL::clean() {
	// Destroy window
	SDL_DestroyWindow(sdlWindow);

	// Destroy renderer
	SDL_DestroyRenderer(m_Renderer);

	// Exit window
	SDL_Quit();
}
