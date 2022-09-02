#include "Player.h"
#include "Enemy.h"
#include "Start.h"
#include "Background.h"
#include <iostream>
#include <exception>
#include <Windows.h>
#include <MMSystem.h>

#pragma comment(lib, "Winmm.lib")

using namespace std;

// speed step movement of enemy
#define STEP 8

// Initialise constructor
Player::Player()
{
	// Initialise varibales
	m_f = SDL_FLIP_NONE;
	m_angle = 0;
	m_execution = true;
	m_isAttacking = false;
	m_playerAttackDone = false;

	move_right = new Vector2D(STEP, 0);
	move_left = new Vector2D(-STEP, 0);
}

// Player destructor
Player::~Player()
{
}

// Initialise sound object
SoundEffect* attackSoundEffect = new SoundEffect();
SoundEffect* winSoundEffect = new SoundEffect();


// parametised draw method
void Player::draw(int m_frame, const char* path, int m_pos_x, int m_pos_y)
{
	try {

		my_frame = m_frame;

		// Load images with other file extension like png, jpg etc.
		m_Surface = IMG_Load(path); // Any files extension for images

		//Check validation of surface if created or not
		if (m_Surface != nullptr) {
			cout << "Load Surface successfully! \n";
		} else cout << "Load Surface unsuccessfully! \n";

		//Create Texture from the surface to loads image to the graphics hardware memory
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (m_Texture != nullptr) {
			cout << "Load Texture successfully! \n";
		} else cout << "Load Texture unsuccessfully! \n";


		// Set the source rectangle
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w / m_frame;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectangle
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_sourceRectangle.w/2;
		m_destinationRectangle.h = m_Surface->h/2;

		//Free the main memory from surface
		SDL_FreeSurface(m_Surface);

	}
	// catch the exception error
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// another  parametised draw method
void Player::drawAttack(int m_frameAttack, const char* path, int m_pos_x, int m_pos_y)
{
	try {
		my_frameAttack = m_frameAttack;

		// Create surface from an image
		m_Surface = IMG_Load(path); // Any files extension for images

		if (m_Surface != nullptr) {
			cout << "Load Surface successfully! \n";
		}
		else cout << "Load Surface unsuccessfully! \n";


		//Create Texture from the surface
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (m_Texture != nullptr) {
			cout << "Load Texture successfully! \n";
		}
		else cout << "Load Texture unsuccessfully! \n";

		SDL_RenderClear(m_Renderer);

		///Set the source rectangle
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w / my_frameAttack;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectanhgke
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_sourceRectangle.w/2;
		m_destinationRectangle.h = m_Surface->h/2;

		//Free the memory from surface
		SDL_FreeSurface(m_Surface);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// Render method definition wiht SDL_RenderPresent
void Player::render()
{
	try {
		//Copy the texture in the rendering
		SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, m_angle, NULL, m_f);

		//Draw in the rendering window
		SDL_RenderPresent(m_Renderer);
	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// Update  definition for player frames 
void Player::update()
{
	try {

		//m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 150) % my_frame);
		m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 50) % my_frame);
	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// updateAttack definition for which implement music while attacking
void Player::updateAttack()
{
	try {
		attackSoundEffect->playMusic();	
	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
	
}

Background* background = new Background();


// handleEvents method definition
void Player::handleEvents() {

	m_isAttacking = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_PRESSED:
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				m_isAttacking = true;					
				updateAttack();	

				break;

			case SDLK_LEFT:
				if (getPosPlayer().x > 0) {		
					playerMove(move_left);
					m_f = SDL_FLIP_HORIZONTAL;
					m_angle = 0;
					update();
				}
				
				break;

			case SDLK_RIGHT:// 1280, 940, 
				if (getPosPlayer().x < 1280 - getPosPlayer().w) {
					playerMove(move_right);
					m_f = SDL_FLIP_NONE;
					m_angle = 0;
					update();
				}	

				break;

			case SDLK_UP:
				if (getPosPlayer().y > 0) {
					//m_isAttacking = false;
					m_destinationRectangle.y -= STEP;
					m_f = SDL_FLIP_NONE;
					m_angle = -90;
					update();
				}

				break;

			case SDLK_DOWN:
				if (getPosPlayer().y < 920 - getPosPlayer().h) {
					//m_isAttacking = false;
					m_destinationRectangle.y += STEP;
					m_f = SDL_FLIP_NONE;
					m_angle = 90;
					update();
				}

				break;

			case SDLK_y:
				m_execution = true;
				break;

			case SDLK_n:
				if (background->execution() == true) {
					m_execution = false;
				}

				break;
			}

			break;	
		}
	}
}

// execution method definition
bool Player::execution() {
	return m_execution;
}

// execution method definition
bool Player::isAttacking() {
	return m_isAttacking;
}

// execution method definition
bool Player::playerAttackDone() {
	return m_playerAttackDone;
}


// playerMove method definition
void Player::playerMove (Vector2D* vec)
{
	m_destinationRectangle.x += vec->getX();
	m_destinationRectangle.y += vec->getY();
}

SDL_Rect Player::getPosPlayer()
{
	SDL_Rect m_player = m_destinationRectangle;
	m_player.x = m_destinationRectangle.x;
	m_player.y = m_destinationRectangle.y;
	m_player.w = m_destinationRectangle.w;
	m_player.h = m_destinationRectangle.h;

	return m_player;
}

// clearScreen method definition
void Player::clearScreen() {
	SDL_RenderClear(m_Renderer);
}





