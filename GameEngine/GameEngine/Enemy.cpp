#include "Enemy.h"
#include <iostream>
#include <exception>


using namespace std;

// Initialise constructor
Enemy::Enemy()
{
	m_f = SDL_FLIP_NONE;
	m_angle = 0;
	//m_execution = true;
	//m_execution = true;
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

		// Set Colour of the  background image
		//SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);// green
		//SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 0);// white
		//SDL_RenderClear(m_Renderer);

		////Set Colour of the texture image 
		//SDL_SetTextureColorMod(m_Texture, 255, 0, 0);

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


// parametised render method
void Enemy::render()
{
	try {

		// To clean the screen before any rendering
		//SDL_RenderClear(m_Renderer);

		// Window Background color
		//SDL_SetRenderDrawColor(m_Renderer, 0x25, 0x23, 0x44, 0x20);

		//Copy the texture in the rendering
		SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, m_angle, NULL, m_f);

		/*SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, 45, NULL, SDL_FLIP_HORIZONTAL);*/

		/*SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, 0, NULL, SDL_FLIP_VERTICAL);*/


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

// clearScreen method definition
void Enemy::clearScreen() {
	SDL_RenderClear(m_Renderer);
}

