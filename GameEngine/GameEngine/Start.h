#pragma once
#include "LoadSDL.h"
#include <SDL_image.h>
#include <Windows.h>


class Start : LoadSDL
{
public:
	Start();
	~Start();
	void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	//void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height);

	//void render(int m_angle, char m_flip);
	void render();
	void update();
	void handleEvents();
	bool execution();
	void clearScreen(); // Clear screen after closing the menu window
	bool option();
	bool mechanics();

private:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int my_frame;
	bool m_execution;
	bool m_option;
	bool m_mechanics;
};