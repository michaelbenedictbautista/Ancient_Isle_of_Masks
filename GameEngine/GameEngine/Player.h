#pragma once

#include "LoadSDL.h"
#include "Vector2D.h"
#include <SDL_image.h>
#include "SoundEffect.h"


class Player : LoadSDL
{
public:
	Player();
	~Player();

	void draw(int m_frame, const char* path, int m_pos_x, int m_pos_y);
	void drawAttack(int m_frameAttack, const char* path, int m_pos_x, int m_pos_y);
	

	//void render(int m_angle, char m_flip);
	void render();
	//void renderAttack();

	void update();
	void updateAttack();

	void handleEvents();
	bool execution();

	
	bool isAttacking();
	bool playerAttackDone();
	void playerMove(Vector2D* vec);
	SDL_Rect getPosPlayer();
	void clearScreen(); // Clear screen after closing the menu window

	//void playMusic();

private:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;
	//SDL_GetKeyState* m_getKeyState;

	int my_frame;
	int my_frameAttack;
	//int my_frameAttack;
	SDL_RendererFlip m_f;
	int m_angle;
	bool m_execution;
	bool m_isAttacking;
	bool m_playerAttackDone;

	Vector2D* move_right;
	Vector2D* move_left;

	//void myDraw(int m_frame, const char* path, int m_pos_x, int m_pos_y);

};

