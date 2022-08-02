#pragma once
#include "LoadSDL.h"
#include <SDL_image.h>

class Enemy : LoadSDL
{
public:
	Enemy();
	~Enemy();

	void draw(const char* path, int m_pos_x, int m_pos_y);
	//void draw(const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height);
	//void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	//void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height);

	//void render(int m_angle, char m_flip);
	void render();

	// Get exact X and Y position of enemy
	SDL_Rect getPosEnemy();

	// Clears the screen 
	void clearScreen();

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

