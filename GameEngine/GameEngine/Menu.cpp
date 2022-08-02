#include "Menu.h"
#include "Resource.h"
#include <SDL_syswm.h>
#include <iostream>

using namespace std;

Menu::Menu()
{
	_window = FindWindow(NULL, L"My Game");
	if (_window == NULL) {
		cout << "Failed to find window.";
		exit(1);
	}
	_menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	if (_menu == NULL) {
		cout << "Failed to create menu.";
		exit(1);
	}
	if (SetMenu(_window, _menu) == 0) {
		cout << "Failed to set menu.";
			exit(1);
	}
	Uint8 event_state_result = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	if (event_state_result == SDL_ENABLE) {
		cout << "Failed to enable Windows event state.";
		exit(1);
		}
}
Menu::~Menu()
{
}

void Menu::get_menu()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_SYSWMEVENT:
			if(event.syswm.msg->msg.win.wParam == ID_FILE_NEWWINDOW) {
				cout << "ID_FILE_NEWWINDOW= " << ID_FILE_NEWWINDOW << "\n";

				// Create new SDL window
				if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

					// A new window for rendering
					sdlWindow2 = SDL_CreateWindow("Sub game",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN );
				}

				// Render the created wundow (sdlWindow2)
				mRenderer2 = SDL_CreateRenderer(sdlWindow2, 0, -1);

			}
			else if (event.syswm.msg->msg.win.wParam == ID_FILE_EXIT) {
				cout << "ID_FILE_EXIT= " << ID_FILE_EXIT << "\n";
				SDL_DestroyWindow(sdlWindow2);
				SDL_DestroyRenderer(mRenderer2);
			}
			else if (event.syswm.msg->msg.win.wParam == ID_HELP_ABOUTGAME) {
				cout << "ID_HELP_ABOUTGAME= " << ID_HELP_ABOUTGAME << "\n";
				displayDialogBox();
			}
		}
	}
}

// Method to display message when once about game option is clicked.
int Menu::displayDialogBox() {
	int msgBoxID = MessageBox(NULL, L"This game called is Yurnero, a hero from the Ancient Isle of Masks that seeks vengeance against the dark lord of Dire.\nPlease press Space Bar to play.", L"Basic Game Engine Project.",
		MB_ICONASTERISK| MB_OK);
	return msgBoxID;
}
