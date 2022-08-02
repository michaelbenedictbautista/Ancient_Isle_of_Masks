#pragma once
#include "LoadSDL.h"
#include <SDL_image.h>

class Background : LoadSDL
{
public:
	Background();
	~Background();
	void draw(const char* path, int m_pos_x, int m_pos_y);
	void render();
	void drawDied(const char* path, int m_pos_x, int m_pos_y);
	void renderDied();
	void clearScreen();
	bool execution();
	void handleEvents();

private:

	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int my_frame;
	SDL_RendererFlip m_f;
	int m_angle;
	bool m_execution;

};

