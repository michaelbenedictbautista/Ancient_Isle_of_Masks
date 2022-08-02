#pragma once
#include "LoadSDL.h"
#include <SDL_ttf.h>
#include <string>

using namespace std;

class TextScreen : LoadSDL
{
public:
	TextScreen();
	~TextScreen();
	void draw(int font_size, string font_path, int posX, int posY);
	void render();
	void update(string str);
	void loadFont(const char*);
	
private:
	string m_font_path;
	int m_font_size;
	int m_posX;
	int m_posY;
	TTF_Font* m_ttf_font;
	SDL_Surface* text_surface;
	SDL_Texture* text_texture;
	SDL_Color text_color;
	SDL_Rect m_text_rectangle;



};

