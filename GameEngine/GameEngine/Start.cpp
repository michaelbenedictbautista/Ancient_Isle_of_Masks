#include "Start.h"
#include <iostream>
#include <exception>

using namespace std;

// Initialise constructor
Start::Start()
{
	m_execution = true;
	m_option = false;
	m_mechanics = false;
}

// Start destructor
Start::~Start()
{
}

// parametised draw method
void Start::draw(int m_frame, const char* path, int m_pos_x, int m_pos_y)
{
	try {
		my_frame = m_frame;
		
		// Create surface from an image
		//m_Surface = SDL_LoadBMP(path);
		m_Surface = IMG_Load(path); // Any file extension for images
		if (m_Surface != nullptr) {
			cout << "Load Surface successfully! \n";
		}
		//Create Texture from the surface
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (m_Texture != nullptr) {
			cout << "Load Texture successfully! \n";
		}

		
		//Set the source rectangle
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w;
		m_sourceRectangle.h = m_Surface->h;

		// Set the destination recctangle
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_sourceRectangle.w/2;
		m_destinationRectangle.h = m_Surface->h/2;

		// Free the memory from surface
		SDL_FreeSurface(m_Surface);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// Render method definition
void Start::render()
{
	try {
		//Copy the texture in the rendering
		SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, 0, NULL, SDL_FLIP_NONE);

		//Draw in the rendering window
		SDL_RenderPresent(m_Renderer);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// update function definition that divides the image on depends on frame
void Start::update()
{
	try {
		m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 150) % my_frame);

	}
	catch (exception& ex) {
		cout << "Exception Caught \n" << ex.what();
	}
}

// getter for execution
bool Start::execution() {
	return m_execution;
}

// getter for option
bool Start::option() {
	return m_option;
}

// getter for mechanics
bool Start::mechanics() {
	return m_mechanics;
}

// HandleEvents method definition
void Start::handleEvents() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:

			switch (event.key.keysym.sym) {
			case SDLK_1:
				m_execution = false;
				break;

			case SDLK_SPACE:
				m_execution = false;
				break;

			case SDLK_RETURN:
				m_execution = false;
				break;
			 

			case SDLK_2:
				m_option = !m_option;

				break;

			case SDLK_3:
				m_mechanics = !m_mechanics;
				break;

			case SDLK_4:
				exit(1);
				break;

			case SDLK_ESCAPE:
				exit(1);
				break;

			}
			
			break;
		}
	}
}

// clearScreen method definition
void Start::clearScreen() {
	SDL_RenderClear(m_Renderer);
}


