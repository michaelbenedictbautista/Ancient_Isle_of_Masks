#pragma once
#include <SDL.h>
#include <Windows.h>

class Menu
{
public:
	Menu();
	~Menu();
	void get_menu();
	int displayDialogBox();

private:
	HWND _window;
	HMENU _menu;

	// Load another window for menu
	SDL_Window* sdlWindow2;
	SDL_Renderer* mRenderer2;

};

