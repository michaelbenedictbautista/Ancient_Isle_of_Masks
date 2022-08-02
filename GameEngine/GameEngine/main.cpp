#include <SDL.h>
#include "LoadSDL.h"
#include "Player.h"
#include "Enemy.h"
#include "Start.h"
#include "Player.h"
#include "Menu.h"
#include <iostream>
#include <exception>
#include <Windows.h>
#include <MMSystem.h>
#include <mciapi.h>
#include "TextScreen.h"
#include "Sound.h"
#include "SoundEffect.h"
#include "Creep.h"
#include "Background.h"


#pragma comment(lib, "Winmm.lib")

using namespace std;


int main(int argc, char** argv) {

	try {
		// Create an object from LoadSDL class
		LoadSDL* loadSDL = new LoadSDL();

		// Instantiate object for player
		Player* player1 = new Player();
		Player* playerAttack = new Player();

		// Instantiate object for enemy
		Enemy* finalEnemy = new Enemy();
		Enemy* enemyDied = new Enemy();


		// Instantiate object for Start
		Start* start1 = new Start();
		Start* start2 = new Start();
		Start* start3 = new Start();
		
		//Instantiate object of TextScreen
		TextScreen* scoreText = new TextScreen();

		Sound* menuStartMusic = new Sound("assets/menuStartMusic.wav");
		Sound* inGameMusic = new Sound("assets/inGameMusic.mp3"); 
		SoundEffect* winSoundEffect = new SoundEffect();

		//Instantiate object for creep
		/*Creep* creep[0] = new Creep();
		Creep* creep[1] = new Creep();
		Creep* creep[2] = new Creep();*/

		Creep* creep = new Creep[3];
		


		//Instantiate object for Background
		Background* inGameBackgroundImage = new Background();
		Background* yurneroDied = new Background();

	
		// Call the loadSDL method
		loadSDL->load(); 
		
		// Instantiate object for Menu
		Menu* menu1 = new Menu();
		//Menu* menu2 = new Menu();

		// Draw start image
		start1->draw(1, "assets/startMenu.jpg", 0, 0);
		start2->draw(1, "assets/controls.jpg", 0, 0);
		start3->draw(1, "assets/mechanics.jpg", 0, 0);
		

		// Validate loading of sounds and play music
		if (Mix_PlayChannel(-1, menuStartMusic->wave(), 0 == -1)) {
			cerr << "Failed to play sound effect! \n";
		}

		
		start1->handleEvents();
		menu1->displayDialogBox() == 1; menu1->displayDialogBox() == 1;
		// Loop while start screen is being executed
		while (start1->execution()) {
			start1->render();
			start1->handleEvents();
			menu1->get_menu();
			if (start1->option() == false) {
				while (start2->execution()) {

					start2->render();
					start2->handleEvents();

				}
			}
			else if (start1->mechanics() == false) {
				while (start3->execution()) {

					start3->render();
					start3->handleEvents();

				}
			}
		}

		// Clears start1 and start2 screen
		start1->clearScreen();
		start2->clearScreen();
		start3->clearScreen();
	
		// Stop menu background music
		Mix_FreeChunk(menuStartMusic->wave());

		// Call the draw method for player, creeps and finalEnemy
		inGameBackgroundImage->draw("assets/inGameBackgroundImage.jpg", 0, 0);
		player1->draw(8, "assets/playerWalk3.png", 50, 100);
		creep[0].draw(1, "assets/creep1.png", 300, 100);
		creep[1].draw(1, "assets/creep2.png", 600, 300);
		creep[2].draw(1, "assets/creep3.png", 900, 600);
		finalEnemy->draw("assets/enemy2.png", 1280-(finalEnemy->getPosEnemy().w + 175), 940 -(finalEnemy->getPosEnemy().h + 140));

		// Call the draw method for finalEnemy when collsion happened.
		enemyDied->draw("assets/creepsDied.png", 500, 600);

		// Display score and life
		scoreText->draw(30, "assets/HarriText-SemiBold.ttf", 540, 30);
		int score = 0;
		int life = 10;

		// Verify loading of sounds and play music
		if (Mix_PlayMusic(inGameMusic->music(), 1 == -1)) {
			cerr << "Failed to play music! \n";
		}

		// Player execution
		while (player1->execution()) 
		{			
			scoreText->update("Score: " + to_string(score) + "  |  " + "Life: " + to_string(life));
			scoreText->render();

			creep[0].update1();
			creep[1].update2();	
			creep[2].update2();

			creep[0].render();
			creep[1].render();
			creep[2].render();

			finalEnemy->render();
			player1->handleEvents();
			player1->render();		
			inGameBackgroundImage->render();

			if (life == 0) {
				inGameBackgroundImage->clearScreen();
				yurneroDied->handleEvents(); 
				yurneroDied->drawDied("assets/yurneroDied.jpg", 0, 0);
				while (yurneroDied->execution()) {
					
					
					!player1->execution();
					yurneroDied->handleEvents();
					yurneroDied->renderDied();
					
				}
			}
			
			if (player1->isAttacking()==true) {	
				player1->update();
								
				player1->drawAttack(1, "assets/attack2.png", player1->getPosPlayer().x, player1->getPosPlayer().y);
				inGameBackgroundImage->render();
				scoreText->render();
				finalEnemy->render();
				creep[0].render();
				creep[1].render();
				creep[2].render();
				player1->render();
				SDL_Delay(100);
				player1->draw(8, "assets/playerWalk3.png", player1->getPosPlayer().x, player1->getPosPlayer().y);

				// Attacking Final Enemy
				if ((finalEnemy->getPosEnemy().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
					(player1->getPosPlayer().x - finalEnemy->getPosEnemy().x < finalEnemy->getPosEnemy().w) &&
					(finalEnemy->getPosEnemy().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
					(player1->getPosPlayer().y - finalEnemy->getPosEnemy().y < finalEnemy->getPosEnemy().h)) {
					
					enemyDied->render();
					finalEnemy->render();
					SDL_Delay(100);
					
					
				}
			
				// Attacking Creeps
				else if ((creep[0].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w + 50) &&
					(player1->getPosPlayer().x - creep[0].getPosCreep().x < creep[0].getPosCreep().w + 50) &&
					(creep[0].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h + 50) &&
					(player1->getPosPlayer().y - creep[0].getPosCreep().y < creep[0].getPosCreep().h + 50)) {
					creep[0].update();
					creep[1].draw(1, "assets/creepsDied.png", creep[1].getPosCreep().x, creep[1].getPosCreep().y);
					
					/** Conditional statement for removing the creeps killed in the screenand apply to
					 collision with creeps without attacking*/




					++score;
					SDL_Delay(100);
					
				}
						
			}
			// Collision with creeps without attacking
			if ((player1->isAttacking() == false)  && (creep[0].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
				(player1->getPosPlayer().x - creep[0].getPosCreep().x < creep[0].getPosCreep().w) &&
				(creep[0].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
				(player1->getPosPlayer().y - creep[0].getPosCreep().y < creep[0].getPosCreep().h)) {
				--life;
			}

			
			/*player1->render();
			player1->draw(8, "assets/playerWalk3.png", player1->getPosPlayer().x, player1->getPosPlayer().y);*/
			
			//score--;

			//Collision with final enemy
	
			//// Function when player and Final enemy meets
			//if (abs(player1->getPosPlayer().x - finalEnemy->getPosEnemy().x) < 50 &&
			//	abs(player1->getPosPlayer().y - finalEnemy->getPosEnemy().y) < 50) {

			//	cout << "Enemy defeated!" << endl;
			//	// overriding method to play music during victory
			//	winSoundEffect->playMusic(); {
			//		PlaySound(TEXT("assets/winSoundEffect.wav"), NULL, SND_ASYNC);
			//		
			//	}
			//	!player1->execution();
			//	SDL_Delay(5000);
			//	//exit(1);
			//}

		}

		// Stop music
		Mix_FreeMusic(inGameMusic->music());
		finalEnemy->clearScreen();
		
		scoreText->update("You win: " + to_string(score));

		scoreText->render();
		player1->render();

		//free up memory used.
		delete player1;
		delete finalEnemy;
	
		SDL_Delay(2000);
		loadSDL->clean(); // call the clean method
		return 0;

	}catch (exception ex) {
		cout << "Exception Caught \n" << ex.what();
	}	
	return 0;
}
