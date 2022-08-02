#pragma once
#include "LoadSDL.h"

class GameObject : LoadSDL
{
public:
	GameObject();
	~GameObject();
	void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height);

	void render(int m_angle, char m_flip);
	void render();
	void update(int m_speed);

private: 
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int my_frame;
};