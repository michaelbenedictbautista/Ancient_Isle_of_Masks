#include "TextScreen.h"
#include <iostream>

using namespace std;

TextScreen::TextScreen()
{
}
TextScreen::~TextScreen()
{
}
void TextScreen::draw(int font_size, string font_path, int posX, int posY) {
	m_font_path = font_path;
	m_font_size = font_size;
	m_posX = posX;
	m_posY = posY;


	text_color = { 0,255,255,255 };
	/*m_text_rectangle.x = m_posX;
	m_text_rectangle.y = m_posY;*/
	m_text_rectangle.x = m_posX;
	m_text_rectangle.y = m_posY;
	
	

}
void TextScreen::update(string str)
{
	loadFont(str.c_str());
	SDL_QueryTexture(text_texture, nullptr, nullptr, &m_text_rectangle.w, &m_text_rectangle.h);
}

void TextScreen::render()
{
	//SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255); // obstacle Rectangle
	//SDL_RenderClear(m_Renderer); //clear the screen
	SDL_RenderCopy(m_Renderer, text_texture, nullptr, &m_text_rectangle);
}

void TextScreen::loadFont(const char* message_text)
{
	m_ttf_font = TTF_OpenFont(m_font_path.c_str(), m_font_size);
	text_surface = TTF_RenderText_Solid(m_ttf_font, message_text, text_color);
	text_texture = SDL_CreateTextureFromSurface(m_Renderer, text_surface);
	SDL_FreeSurface(text_surface);
}
