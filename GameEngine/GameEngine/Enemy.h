#pragma once
#include "LoadSDL.h"
#include "Vector2D.h"
#include <SDL_image.h>

class Enemy : LoadSDL
{
public:
	Enemy();
	~Enemy();

	void draw(const char* path, int m_pos_x, int m_pos_y);
	void drawFinalEnemy(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	//void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	//void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height);

	//void render(int m_angle, char m_flip);
	void render();
	void renderFinalEnemy();

	void updateBouncing();
	void updateTaunt();
	bool execution();

	// Get exact X and Y position of enemy
	SDL_Rect getPosEnemy();

	void enemyMove(Vector2D* vec);

	// Clears the screen 
	void clearScreen();
	int finalEnemyExist;

private:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	int my_frame;
	SDL_RendererFlip m_f;
	int m_angle;
	int my_finalEnemyExist;
	bool m_execution;

	Vector2D* move_right;
	Vector2D* move_left;
	Vector2D* move_up;
	Vector2D* move_down;

	Vector2D* move_bouncing;

};

