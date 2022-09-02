#include "Background.h"
#include "Player.h"
#include <iostream>
#include <exception>

using namespace std;

// Initialise constructor
Background::Background()
{
	// Intialise variables
	m_f = SDL_FLIP_NONE;
	m_angle = 0;
	m_execution = false;
	
}

// Background destructor
Background::~Background()
{
}

// Parametised draw background image
void Background::draw(int m_frame, const char* path, int m_pos_x, int m_pos_y)
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
void Background::render()
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

void Background::drawLayout(int m_frame, const char* path, int m_pos_x, int m_pos_y)
{
	try {
	
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
		m_sourceRectangle.w = m_Surface->w;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination rectangle
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_sourceRectangle.w / 2;
		m_destinationRectangle.h = m_Surface->h / 2;

		//Free the memory from surface
		SDL_FreeSurface(m_Surface);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// parametised render method
void Background::renderLayout()
{
	try {

		// To clean the screen before any rendering
		SDL_RenderClear(m_Renderer);

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

// Update  definition
void Background::update()
{
	try {	
		m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 50) % my_frame);
	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}


void Background::handleEvents() {
	
	m_execution = true;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit(1);

				break;

			case SDLK_y:
				
				break;

			case SDLK_n:
				m_execution = false;
								
				break;

			case SDLK_4:
				exit(1);

				break;
			} 
			break;
		}
	}
}

// Clears the screen
void Background::clearScreen() {
	SDL_RenderClear(m_Renderer);
}

// execution method definition
bool Background::execution() {
	return m_execution;
}
