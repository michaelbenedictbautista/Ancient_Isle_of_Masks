#pragma once
#include "LoadSDL.h"
#include "Vector2D.h"
#include <SDL_Image.h>


class Creep : LoadSDL
{
public:
	Creep();
	~Creep();

	void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	//void draw(const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height);

	//void render(int m_angle, char m_flip);
	void render();

	void update();
	void update1();
	void update2();
	//void handleEvents();
	bool execution();
	int creepDied;

	void creepMove(Vector2D* vec);
	SDL_Rect getPosCreep();
	void clearScreen();



private:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int my_frame;
	int my_creepDied;
	SDL_RendererFlip m_f;
	int m_angle;
	bool m_execution;


	Vector2D* move_right;
	Vector2D* move_left;
	Vector2D* move_bouncing;

};

