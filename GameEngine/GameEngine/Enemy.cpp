#include "Enemy.h"
#include <iostream>
#include <exception>
#include "Creep.h"

using namespace std;

// speed step movement of enemy
#define STEP 8

//#define GRAVITY 0; //for quick testing
#define GRAVITY 4;

int gravityEnemy = GRAVITY;
int enemyStep = STEP;

// Initialise constructor
Enemy::Enemy()
{
	// Initialise variables
	m_f = SDL_FLIP_NONE;
	m_angle = 0;
	my_finalEnemyExist = 1;
	m_execution = true;

	move_right = new Vector2D(STEP, 0);
	move_left = new Vector2D(-STEP, 0);
	move_bouncing = new Vector2D(40, 10);
	

	/*move_up = new Vector2D(0, STEP);
	move_down= new Vector2D(0, -STEP);*/
}

// Enemy destructor
Enemy::~Enemy()
{
}

// parametised draw method
void Enemy::draw(const char* path, int m_pos_x, int m_pos_y)
{
	try {
		//my_frame = m_frame;
		// Create surface from an image
		//m_Surface = SDL_LoadBMP(path); // BMP file extension for images
		m_Surface = IMG_Load(path); // Any files extension for images

		if (m_Surface != nullptr) {
			cout << "Load Surface successfully! \n";
		} else cout << "Load Surface unsuccessfully! \n";


		//Create Texture from the surface
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (m_Texture != nullptr) {
			cout << "Load Texture successfully! \n";
		} else cout << "Load Texture unsuccessfully! \n";

		///Set the source rectangle
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectangle
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
// parametised draw method
void Enemy::drawFinalEnemy(int m_frame, const char* path, int m_pos_x, int m_pos_y)
{
	try {
		my_frame = m_frame;
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

		///Set the source rectangle
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w / m_frame;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectangle
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


// parametised render method
void Enemy::render()
{
	try {

		//Copy the texture in the rendering
		SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, m_angle, NULL, m_f);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}


}

// parametised render method
void Enemy::renderFinalEnemy()
{
	try {

		//Copy the texture in the rendering
		SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, m_angle, NULL, m_f);

		//Draw in the rendering window
		//SDL_RenderPresent(m_Renderer);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

SDL_Rect Enemy::getPosEnemy()
{
	SDL_Rect m_enemy = m_destinationRectangle;
	m_enemy.x = m_destinationRectangle.x;
	m_enemy.y = m_destinationRectangle.y;
	m_enemy.w = m_destinationRectangle.w;
	m_enemy.h = m_destinationRectangle.h;

	return m_enemy;
}


void Enemy::updateTaunt() {
	m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 150) % my_frame);
}

void Enemy::updateBouncing()
{
	
		try {
			
			// Horizontalal Vertical movement
			move_bouncing->setY(move_bouncing->getY() + gravityEnemy); 
			enemyMove(move_bouncing);
			
			if (getPosEnemy().y > (940 - getPosEnemy().h) ||
				getPosEnemy().y < 0) {
				move_bouncing->setY(-1 * move_bouncing->getY());
			}

			if (getPosEnemy().y > (880 - getPosEnemy().h) &&
				abs(move_bouncing->getY()) < 2 * gravityEnemy) {
				move_bouncing->setY(0);

			}
			else {
				move_bouncing->setY(move_bouncing->getY() + gravityEnemy);
			}

			if (getPosEnemy().y > 900 - getPosEnemy().h) {
				m_destinationRectangle.y = 750;
			}
			
			if (m_destinationRectangle.x > (1280 - m_destinationRectangle.w) ||
				m_destinationRectangle.x < 0) {
				move_bouncing->setX(-1 * move_bouncing->getX());

				if (m_f == SDL_FLIP_NONE) {
					m_f = SDL_FLIP_HORIZONTAL;
				}
				else {
					m_f = SDL_FLIP_NONE;
				}
			}

			if (m_destinationRectangle.x > (600 - m_destinationRectangle.w) &&
				abs(move_bouncing->getX()) < 2 * gravityEnemy) {
				move_bouncing->setX(0);
			}
			else {
				move_bouncing->setX(move_bouncing->getX() + gravityEnemy);
			}
			if (m_destinationRectangle.x > 1280 - m_destinationRectangle.w) {
				m_destinationRectangle.x = 920;
			}

		}
		catch (exception& ex) {
			cout << "Exception Caught \n" << ex.what();
		}
}

// Execution method definition
bool Enemy::execution() {
	return m_execution;
}

//// CreepMove method definition
void Enemy::enemyMove(Vector2D* vec)
{
	m_destinationRectangle.x += vec->getX();
	m_destinationRectangle.y += vec->getY();
}


// ClearScreen method definition
void Enemy::clearScreen() {
	SDL_RenderClear(m_Renderer);
}

