#include "Creep.h"
#include "Enemy.h"
#include <iostream>
#include <exception>

using namespace std;
#define STEP 8

//#define GRAVITY 4; // to move creeps
#define GRAVITY 4;

static int gravity = GRAVITY;
int creepStep = STEP;

// Initialise constructor
Creep::Creep()
{
	
	m_f = SDL_FLIP_NONE;
	m_angle = 0;
	my_creepExist = creepExist;
	m_execution = true;
	my_creepExist = 1;

	move_right = new Vector2D(STEP, 0);
	move_left = new Vector2D(-STEP, 0);
	move_bouncing = new Vector2D(0, 0);
}

// Player destructor
Creep::~Creep()
{
}

// parametised draw method
void Creep::draw(int m_frame, const char* path, int m_pos_x, int m_pos_y)
{
	try {
		my_frame = m_frame;
		// Create surface from an image
		m_Surface = IMG_Load(path); // other type of image
		//m_Surface = SDL_LoadBMP(path);
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

		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectanhgke
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_sourceRectangle.w / 4;
		m_destinationRectangle.h = m_Surface->h / 4;

		//Free the memory from surface
		SDL_FreeSurface(m_Surface);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}
void Creep::drawDied(int m_frame, const char* path, int m_pos_x, int m_pos_y)
{
	try {
		my_frame = m_frame;
		// Create surface from an image
		m_Surface = IMG_Load(path); // other type of image
		//m_Surface = SDL_LoadBMP(path);
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
		m_sourceRectangle.w = m_Surface->w;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectanhgke
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_sourceRectangle.w / 4;
		m_destinationRectangle.h = m_Surface->h / 4;

		//Free the memory from surface
		SDL_FreeSurface(m_Surface);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// Render method definition
void Creep::render()
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

void Creep::renderDied()
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

// update update definition
void Creep::update() {
	m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 50) % my_frame);
}


SDL_Rect Creep::getPosCreep()
{
	SDL_Rect m_creep = m_destinationRectangle;
	m_creep.x = m_destinationRectangle.x;
	m_creep.y = m_destinationRectangle.y;
	m_creep.w = m_destinationRectangle.w;
	m_creep.h = m_destinationRectangle.h;

	return m_creep;
}

// update update definition
void Creep::updateBounceVertically()
{
	try {
		//rectEnemy2->drawing(getPosEnemy2());
		
		// Motion of a creep
		//m_destinationRectangle.y += creepStep; // move vertically only
		move_bouncing->setY(move_bouncing->getY() + gravity); // Vertical
		creepMove(move_bouncing);
	
		// Vertical
		if (getPosCreep().y > (940 - getPosCreep().h) ||
			getPosCreep().y < 0) {
			move_bouncing->setY(-1 * move_bouncing->getY());
		}

		if (getPosCreep().y > (880 - getPosCreep().h) &&
			abs(move_bouncing->getY()) < 2 * gravity) {
			move_bouncing->setY(0);

		}
		else {
			move_bouncing->setY(move_bouncing->getY() + gravity);
		}

		if (getPosCreep().y > 900 - getPosCreep().h) {
			m_destinationRectangle.y = 890;
		}

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}
// update  definition
void Creep::updateBounceHorizontally()
{
	try {

		move_bouncing->setX(move_bouncing->getX() + gravity); // Horizontal
		creepMove(move_bouncing);

		//HORIZONTAL
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
			abs(move_bouncing->getX()) < 2 * gravity) {
			move_bouncing->setX(0);
		}
		else {
			move_bouncing->setX(move_bouncing->getX() + gravity);
		}
		if (m_destinationRectangle.x > 1280 - m_destinationRectangle.w) {
			m_destinationRectangle.x = 1150;
		}
	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// execution method definition
bool Creep::execution() {
	return m_execution;
}

//// creepMove method definition
void Creep::creepMove(Vector2D* vec)
{
	m_destinationRectangle.x += vec->getX();
	m_destinationRectangle.y += vec->getY();
}

void Creep::clearScreen() {
	SDL_RenderClear(m_Renderer);
}


