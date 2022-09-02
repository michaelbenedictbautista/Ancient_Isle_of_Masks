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
	void drawDied(int m_frame, const char* path, int m_pos_x, int m_pos_y);

	//void render(int m_angle, char m_flip);
	void render();
	void renderDied();

	void update();
	void updateBounceHorizontally ();
	void updateBounceVertically();
	//void handleEvents();
	bool execution();
	int creepExist;
	

	void creepMove(Vector2D* vec);
	SDL_Rect getPosCreep();
	void clearScreen();



private:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int my_frame;
	int my_creepExist;
	SDL_RendererFlip m_f;
	int m_angle;
	bool m_execution;


	Vector2D* move_right;
	Vector2D* move_left;
	Vector2D* move_bouncing;

};

