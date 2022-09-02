#pragma once
#include <SDL.h>
#include <SDL_ttf.h>


class LoadSDL
{
// Function declaration
public:
	LoadSDL();
	~LoadSDL();
	void load();
	void clean();

protected:

	// Create surface from an image into the main memory
	static SDL_Renderer* m_Renderer;

private:
	SDL_Window* sdlWindow;
};