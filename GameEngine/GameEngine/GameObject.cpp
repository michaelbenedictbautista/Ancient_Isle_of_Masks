#include "GameObject.h"
#include <iostream>
#include <exception>

using namespace std;

	// GameObject default constructor
	GameObject::GameObject()
	{
	}

	// GameObject destructor
	GameObject::~GameObject()
	{
	}

	// parametised draw method for regular size player 
	void GameObject::draw(int m_frame, const char* path, int m_pos_x, int m_pos_y)
	{
		try {
			my_frame = m_frame;
			// Create surface from an image
			m_Surface = SDL_LoadBMP(path);
			if (m_Surface != nullptr) {
				cout << "Load Surface successfully! \n";
			}
			//Create Texture from the surface
			m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
			if (m_Texture != nullptr) {
				cout << "Load Texture successfully! \n";
			}

			///Set the source rectangle
			m_sourceRectangle.x = 0;
			m_sourceRectangle.y = 0;
			m_sourceRectangle.w = m_Surface->w / m_frame;
			m_sourceRectangle.h = m_Surface->h;

			//Set the destination recctanhgke
			m_destinationRectangle.x = m_pos_x;
			m_destinationRectangle.y = m_pos_y;
			m_destinationRectangle.w = m_sourceRectangle.w;
			m_destinationRectangle.h = m_Surface->h;

			//Free the memory from surface
			SDL_FreeSurface(m_Surface);

		} catch (exception& ex) {
			cout << "Exception Caught \n" << ex.what();
		}
	}
	
	// parametised draw method for larger size player 
	void GameObject::draw(int m_frame, const char* path, int m_pos_x, int m_pos_y, int m_width, int m_height)
	{
		try {
		my_frame = m_frame;
		// Create surface from an image
		m_Surface = SDL_LoadBMP(path);
		if (m_Surface != nullptr) {
			cout << "Load Surface successfully! \n";
		}
		//Create Texture from the surface
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
		if (m_Texture != nullptr) {
			cout << "Load Texture successfully! \n";
		}

		///Set the source rectangle
		m_sourceRectangle.x = 0;
		m_sourceRectangle.y = 0;
		m_sourceRectangle.w = m_Surface->w / m_frame;
		m_sourceRectangle.h = m_Surface->h;

		//Set the destination recctanhgke
		m_destinationRectangle.x = m_pos_x;
		m_destinationRectangle.y = m_pos_y;
		m_destinationRectangle.w = m_width;
		m_destinationRectangle.h = m_height;

		//Free the memory from surface
		SDL_FreeSurface(m_Surface);

		}catch (exception& ex) {
			cout << "Exception Caught \n" << ex.what();
		}
	}

	// Render method definition
	void GameObject::render()
	{
		try {
		//Copy the texture in the rendering
		SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle,
			&m_destinationRectangle, 0, NULL, SDL_FLIP_NONE);

		//Draw in the rendering window
		SDL_RenderPresent(m_Renderer);

		} catch (exception& ex) {
			cout << "Exception Caught \n" << ex.what();
		}
	}

	// update method definition
	void GameObject::update(int m_speed)
	{
		try {
		m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() * m_speed / 150) % my_frame);
		
		} catch (exception& ex) {
			cout << "Exception Caught \n" << ex.what();
		}
	}
