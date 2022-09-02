#include <SDL.h>
#include <iostream>
#include <exception>
#include <Windows.h>
#include <MMSystem.h>
#include <mciapi.h>
#include <time.h>
#include "LoadSDL.h"
#include "Player.h"
#include "Enemy.h"
#include "Start.h"
#include "Player.h"
#include "Menu.h"
#include "TextScreen.h"
#include "Sound.h"
#include "SoundEffect.h"
#include "Creep.h"
#include "Background.h"


#pragma comment(lib, "Winmm.lib")

using namespace std;


int delayTimer( int timer) {
	Sleep(timer);
	//SDL_Delay(timer);
	return timer;
}

int main(int argc, char** argv) {

	

	try {
		// Create an object from LoadSDL class
		LoadSDL* loadSDL = new LoadSDL();

		// Instantiate object for Player
		Player* player1 = new Player();
		Player* playerAttack = new Player();

		// Instantiate object for enemy
		Enemy* finalEnemyInPrison = new Enemy();
		Enemy* finalEnemy = new Enemy();
		Enemy* finalEnemyDied = new Enemy();


		// Instantiate object for Start
		Start* start1 = new Start();
		Start* start2 = new Start();
		Start* start3 = new Start();
		
		// Instantiate object of TextScreen
		TextScreen* scoreAndLifeTextScreen = new TextScreen();
		TextScreen* timerTextScreen = new TextScreen();
		TextScreen* lifeTextScreen = new TextScreen();

		// Instantiate object for Sounds
		Sound* menuStartMusic = new Sound("assets/menuStartMusic.wav");
		Sound* inGameMusic = new Sound("assets/inGameMusic.mp3");
		Sound* yuneroStartMusic = new Sound("assets/yuneroStartMusic.mp3");
		Sound* finalEnemyAppearanceMusic = new Sound("assets/finalEnemyAppearanceMusic.mp3");
		Sound* yurneroDiedMusic = new Sound("assets/yurneroDiedMusic.mp3");
		Sound* enemyStartMusic = new Sound("assets/enemyStartMusic.mp3");
		Sound* winningSoundEffect = new Sound("assets/winningSoundEffect.mp3");
		Sound* creditsMusic = new Sound("assets/creditsMusic.mp3");
		Sound* finalEnemyBattleBGMusic = new Sound("assets/finalEnemyBattleBGMusic.mp3");

		//Instantiate object for array of creeps
		Creep* creep = new Creep[3];
		
		//Instantiate object for Background
		Background* splash = new Background();
		Background* inGameBackgroundImage = new Background();
		Background* yurneroDied = new Background();
		Background* yurneroWon = new Background();
		Background* finalEnemyAppearance = new Background();
		Background* finalEnemyPrison = new Background();
		
		// Initialise score
		int score = 0;

		// Initialise life
		int life = 100;

		// Initialise timer
		int timer = 10000;
		
		
		// Call the loadSDL method
		loadSDL->load(); 
		
		// Instantiate object for Menu
		Menu* menu1 = new Menu();
		
		// Draw start image
		start1->draw(1, "assets/startMenu.jpg", 0, 0);
		start2->draw(1, "assets/controls.jpg", 0, 0);
		start3->draw(1, "assets/mechanics.jpg", 0, 0);
			
		// Validate loading of sounds and play music
		if (Mix_PlayChannel(-1, menuStartMusic->wave(), -1 == -1)) {
			cerr << "Failed to play sound effect! \n";
		}

		// Draw splash screen
		splash->draw(1, "assets/splash.jpg", 0, 0);
		splash->renderLayout();

		SDL_Delay(5000);
		splash->clearScreen();

		start1->handleEvents();
		menu1->displayDialogBox();	// Dialogbox message
		start1->render();

		// Loop while start screen is being executed
		while (start1->execution()) {
			menu1->get_menu();

			if (start1->option()) {			
				start2->render();
			}
			else if (start1->mechanics()) {
				start3->render();
			}
			else  start1->render();
			 start1->handleEvents();
		}

		// Clear screen prior rendering
		start1->clearScreen();
		start2->clearScreen();
		start3->clearScreen();
	
		// Stop menuStartMusic
		Mix_FreeChunk(menuStartMusic->wave());

		// Call the draw method for background, player, creeps and finalEnemyInPrison
		inGameBackgroundImage->draw(1, "assets/inGameBackgroundImage.jpg", 0, 0);
		player1->draw(8, "assets/playerWalk3.png", 50, 100);
		creep[0].draw(1, "assets/creep1.png", 300, 100);
		creep[1].draw(1, "assets/creep2.1.png", 300, 470);
		creep[2].draw(1, "assets/creep3.1.png", 900, 100);

		// boolean that will hold condition if a creep is still alive or dead.
		creep[0].creepExist = 1;
		creep[1].creepExist = 1;
		creep[2].creepExist = 1;

		// boolean that will hold condition if the final enemy is still alive or dead.
		finalEnemy->finalEnemyExist = 1;

		// Call the draw method for finalEnemyInPrison
		finalEnemyInPrison->draw("assets/enemy2.png", 1280-(finalEnemyInPrison->getPosEnemy().w + 175), 940 -(finalEnemyInPrison->getPosEnemy().h + 140));

		// Call the draw method for score and life
		scoreAndLifeTextScreen->draw(30, "assets/HarriText-SemiBold.ttf", 540, 30);
		
		// Verify loading and play yuneroStartMusic
		if (Mix_PlayMusic(yuneroStartMusic->music(), 1 == -1)) {
			cerr << "Failed to play music! \n";
		}
		SDL_Delay(2000);

		// Verify loading and play inGameMusic
		if (Mix_PlayMusic(inGameMusic->music(), -1 == -1)) {
			cerr << "Failed to play music! \n";
		}

		// Implement a while loop from  player property named "execution"  which is a boolean
		while (player1->execution()) 
		{			
			// Update and render score
			scoreAndLifeTextScreen->update("Score: " + to_string(score) + "  |  " + "Life: " + to_string(life));
			scoreAndLifeTextScreen->render();

			// Creeps movement if they still exist
			if (creep[0].creepExist == 1) {
				creep[0].updateBounceVertically();
				
			}
			
			// Creeps movement if they still exist
			if (creep[1].creepExist == 1) {
				creep[1].updateBounceHorizontally();
			}
			
			// Creeps movement if they still exist
			if (creep[2].creepExist == 1) {
				creep[2].updateBounceVertically();
			}
	
			// display all creeps
			creep[0].render();
			creep[1].render();
			creep[2].render();

			// display finalEnemyInPrison
			finalEnemyInPrison->render();
			player1->handleEvents();
			player1->render();
			// display finalEnemyInPrison
			inGameBackgroundImage->render();

			// Conditonal statement when hero's life is down to zero
			if (life <= 0 ) {
				inGameBackgroundImage->clearScreen();
				player1->handleEvents();
				yurneroDied->handleEvents(); 
				yurneroDied->drawLayout(1, "assets/yurneroDied.jpg", 0, 0);

				// Stop music in inGame music
				Mix_FreeMusic(inGameMusic->music());

				// Verify and polay music when yurnero died
				if (Mix_PlayMusic(yurneroDiedMusic->music(), -1 == -1)) {
					cerr << "Failed to play music! \n";
				}
				
				while (yurneroDied->execution()) {
					yurneroDied->handleEvents();
					yurneroDied->renderLayout();

					////////// If I want to continue delete break////////////////
					SDL_Delay(8000);
					break;
			
				}
				yurneroDied->clearScreen();		
				break;				
			}
			
			// Conditonal if a player is in attack mnode which is handled by a boolean "isAttacking"
			if (player1->isAttacking()==true && yurneroDied->execution() ==false ) {
				player1->update();
				
				// draw method and display attack image
				player1->drawAttack(1, "assets/attack2.png", player1->getPosPlayer().x, player1->getPosPlayer().y);
				inGameBackgroundImage->render();
				scoreAndLifeTextScreen->render();
				finalEnemyInPrison->render();

				creep[0].render();
				creep[1].render();
				creep[2].render();
				player1->render();
				SDL_Delay(50);
				player1->draw(8, "assets/playerWalk3.png", player1->getPosPlayer().x, player1->getPosPlayer().y);
		
				// Conditional statement which finds the exact position of the player and creeps for succcessful attack.
				if ((creep[0].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w + 50) &&
				(player1->getPosPlayer().x - creep[0].getPosCreep().x < creep[0].getPosCreep().w + 50) &&
				(creep[0].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h + 50) &&
				(player1->getPosPlayer().y - creep[0].getPosCreep().y < creep[0].getPosCreep().h + 50)) {
																
					if (creep[0].creepExist == 1) {
						score = score + 100;
					}

					/** Conditional statement for removing the creeps killed in the screen and apply to
						collision with creeps without attacking*/
					creep[0].drawDied(1, "assets/creep0Died.png", creep[0].getPosCreep().x, creep[0].getPosCreep().y);					
					creep[0].creepExist = 0;
 					
					// given delay to display a bot of animation for while attacking
					SDL_Delay(50);
					
				}
				else if ((creep[1].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w + 50) &&
					(player1->getPosPlayer().x - creep[1].getPosCreep().x < creep[1].getPosCreep().w + 50) &&
					(creep[1].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h + 50) &&
					(player1->getPosPlayer().y - creep[1].getPosCreep().y < creep[1].getPosCreep().h + 50)) {
					
					if (creep[1].creepExist == 1) {
						score = score + 100;
					}
					
					creep[1].drawDied(1, "assets/creep1Died.png", creep[1].getPosCreep().x, creep[1].getPosCreep().y);
					creep[1].creepExist = 0;

					SDL_Delay(50);

				}
				else if ((creep[2].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w + 50) &&
					(player1->getPosPlayer().x - creep[2].getPosCreep().x < creep[2].getPosCreep().w + 50) &&
					(creep[2].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h + 50) &&
					(player1->getPosPlayer().y - creep[2].getPosCreep().y < creep[2].getPosCreep().h + 50)) {
					
					if (creep[2].creepExist == 1) {
						score = score + 100;
					}

					creep[2].drawDied(1, "assets/creep2Died.png", creep[2].getPosCreep().x, creep[2].getPosCreep().y);
					creep[2].creepExist = 0;					

					SDL_Delay(50);
				}
					
			}
			// Conditional statement which finds the exact position of the player and creeps for possible collisions that weill lead to decrease of hero's life
			if ((player1->isAttacking() == false)  && (creep[0].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
				(player1->getPosPlayer().x - creep[0].getPosCreep().x < creep[0].getPosCreep().w) &&
				(creep[0].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
				(player1->getPosPlayer().y - creep[0].getPosCreep().y < creep[0].getPosCreep().h) && creep[0].creepExist == 1) {
				--life;
			}
			else if ((player1->isAttacking() == false) && (creep[1].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
				(player1->getPosPlayer().x - creep[1].getPosCreep().x < creep[1].getPosCreep().w) &&
				(creep[1].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
				(player1->getPosPlayer().y - creep[1].getPosCreep().y < creep[1].getPosCreep().h) && creep[1].creepExist == 1) {
				--life;
			}
			else if ((player1->isAttacking() == false) && (creep[2].getPosCreep().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
				(player1->getPosPlayer().x - creep[2].getPosCreep().x < creep[2].getPosCreep().w) &&
				(creep[2].getPosCreep().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
				(player1->getPosPlayer().y - creep[2].getPosCreep().y < creep[2].getPosCreep().h) && creep[2].creepExist == 1) {
				--life;
			}
			else if ((finalEnemyInPrison->getPosEnemy().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
				(player1->getPosPlayer().x - finalEnemyInPrison->getPosEnemy().x < finalEnemyInPrison->getPosEnemy().w) &&
				(finalEnemyInPrison->getPosEnemy().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
				(player1->getPosPlayer().y - finalEnemyInPrison->getPosEnemy().y < finalEnemyInPrison->getPosEnemy().h)) {
				--life;
			}
			else if (creep[0].creepExist == 0 && creep[1].creepExist == 0  && creep[2].creepExist == 0) {	
				// Stop music inGameMusic
				Mix_FreeMusic(inGameMusic->music());
				SDL_Delay(2000);

				//  Verify loading of finalEnemyAppearanceMusic
				if (Mix_PlayMusic(finalEnemyAppearanceMusic->music(), 1 == -1)) {
					cerr << "Failed to play music! \n";
				}
				SDL_Delay(3000);

				// clear screen prior rendering other screen
				inGameBackgroundImage->clearScreen();
				finalEnemyPrison->drawLayout(1, "assets/finalEnemyPrison.jpg", 0, 0);
				finalEnemyPrison->renderLayout();
				SDL_Delay(2000);
		
				// Verify loading and play enemyStartMusic
				if (Mix_PlayMusic(enemyStartMusic->music(), 1 == -1)) {
					cerr << "Failed to play music! \n";
				}
				SDL_Delay(7000);

		
				player1->update();
				finalEnemyAppearance->handleEvents();

				// call draw method for finalEnemyAppearance, timerTextScreen, lifeTextScreen, finalEnemy
				finalEnemyAppearance->draw(1, "assets/finalEnemyAppearance.jpg", 0, 0);
				timerTextScreen->draw(30, "assets/HarriText-SemiBold.ttf", 540, 30);
				lifeTextScreen-> draw(30, "assets/HarriText-SemiBold.ttf", 540, 80);				
				finalEnemy->drawFinalEnemy(2, "assets/finalEnemy.png", 600, 100);
				
				// render all necessary classes in the screen.
				finalEnemyAppearance->renderLayout();
				finalEnemyAppearance->render();
				timerTextScreen->update("Timer left: " + to_string(timer));
				lifeTextScreen->update("Life left: " + to_string(life));
				timerTextScreen->render();
				lifeTextScreen->render();
				finalEnemy->renderFinalEnemy();			
				player1->render();				
				player1->draw(8, "assets/playerWalk3.png", player1->getPosPlayer().x, player1->getPosPlayer().y);
				
				SDL_Delay(5000);

				// Verify loading and play finalEnemyBattleBGMusic
				if (Mix_PlayMusic(finalEnemyBattleBGMusic->music(), 1 == -1)) {
					cerr << "Failed to play music! \n";
				}
				
				// Implemented while loop for final enemy and hero's battle
				while (finalEnemyAppearance->execution()) {				
					finalEnemyAppearance->render();
					
					finalEnemy->updateTaunt();
						
					// start timer countdown
					--timer;
								
					// diplay timer and life left in the screen
					timerTextScreen->update("Timer left: " + to_string(timer));
					lifeTextScreen->update("Life left: " + to_string(life));
					timerTextScreen->render();
					lifeTextScreen->render();

					// final enemy random bouncing movement
					finalEnemy->updateBouncing();
					finalEnemy->renderFinalEnemy();

					player1->handleEvents();
					player1->render();

					// Conditional statement when hero is in attacking mode
					if (player1->isAttacking() == true && yurneroDied->execution() == false) {
						player1->update();
										
						player1->drawAttack(1, "assets/attack2.png", player1->getPosPlayer().x, player1->getPosPlayer().y);
						finalEnemyAppearance->render();
						finalEnemy->updateBouncing();
						finalEnemy->renderFinalEnemy();

						timerTextScreen->update("Timer left: " + to_string(timer));
						lifeTextScreen->update("Life left: " + to_string(life));
						timerTextScreen->render();
						lifeTextScreen->render();					

						player1->handleEvents();
						player1->render();
						SDL_Delay(50);
						player1->draw(8, "assets/playerWalk3.png", player1->getPosPlayer().x, player1->getPosPlayer().y);

						if ((finalEnemy->getPosEnemy().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
							(player1->getPosPlayer().x - finalEnemy->getPosEnemy().x < finalEnemy->getPosEnemy().w) &&
							(finalEnemy->getPosEnemy().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
							(player1->getPosPlayer().y - finalEnemy->getPosEnemy().y < finalEnemy->getPosEnemy().h)) {

							if (finalEnemy->finalEnemyExist == 1) {
								++score + 100;
							}

							/** Conditional statement for removing the creeps killed in the screen and apply to
							 collision with creeps without attacking*/
							finalEnemy->drawFinalEnemy(1, "assets/creep1Died.png", finalEnemy->getPosEnemy().x, finalEnemy->getPosEnemy().y);
							finalEnemy->finalEnemyExist = 0;

							SDL_Delay(50);
							break;

						}
						
					}
					// Conditional statement when hero is not attacking and may lead for collisions with the enemy based on theri positions.
					if ((player1->isAttacking() == false) && (finalEnemy->getPosEnemy().x - player1->getPosPlayer().x < player1->getPosPlayer().w) &&
						(player1->getPosPlayer().x - finalEnemy->getPosEnemy().x < finalEnemy->getPosEnemy().w) &&
						(finalEnemy->getPosEnemy().y - player1->getPosPlayer().y < player1->getPosPlayer().h) &&
						(player1->getPosPlayer().y - finalEnemy->getPosEnemy().y < finalEnemy->getPosEnemy().h) && finalEnemy->finalEnemyExist == 1) {
						--life;

						// render hero death background and sound effect.
						if (life <= 0) {
							finalEnemyAppearance->clearScreen();
							player1->handleEvents();
							yurneroDied->handleEvents();
							yurneroDied->drawLayout(1, "assets/yurneroDied.jpg", 0, 0);

							// Verify and polay music when yurnero died
							if (Mix_PlayMusic(yurneroDiedMusic->music(), 3 == -1)) {
								cerr << "Failed to play music! \n";
							}

							while (yurneroDied->execution()) {

								yurneroDied->handleEvents();
								yurneroDied->renderLayout();

						
								SDL_Delay(5000);
								break;
							}
						
							yurneroDied->clearScreen();

							break;
						}
					}
				}

				SDL_Delay(5000);
				if (finalEnemy->finalEnemyExist == 0) {
					// Verify loading and play winningSoundEffect
					if (Mix_PlayMusic(winningSoundEffect->music(), -1 == -1)) {
						cerr << "Failed to play music! \n";
					}

					// load image when hero won the battle
					yurneroWon->drawLayout(1, "assets/yurneroWon.jpg", 0, 0);
					yurneroWon->renderLayout();

					SDL_Delay(5000);

					

				}
				break;
			}
		}
	
		SDL_Delay(5000);
		// Verify loading of enemyStartMusic
		if (Mix_PlayMusic(creditsMusic->music(), -1 == -1)) {
			cerr << "Failed to play music! \n";
		}

		// clear screens and  load image for credits
		yurneroWon->clearScreen();
		yurneroWon->drawLayout(1, "assets/creepsEnd.jpg", 0, 0);
		yurneroWon->renderLayout();
		SDL_Delay(8000);
		
		// clear screens and  load image for credits
		yurneroWon->clearScreen();
		yurneroWon->drawLayout(1, "assets/enemyEnd.jpg", 0, 0);
		yurneroWon->renderLayout();
		SDL_Delay(8000);
		
		// clear screens and  load image for credits
		yurneroWon->clearScreen();
		yurneroWon->drawLayout(1, "assets/heroEnd.jpg", 0, 0);
		yurneroWon->renderLayout();
		SDL_Delay(8000);
		
		//free all up memory used.
		delete splash;
		delete inGameBackgroundImage;
		delete yurneroDied;
		delete yurneroWon;

		delete finalEnemyAppearance;
		delete finalEnemyPrison;
		delete finalEnemyDied;

		delete scoreAndLifeTextScreen;
		delete timerTextScreen;
		delete lifeTextScreen;

		delete player1;
		delete playerAttack;
		
		delete start1;
		delete start2;
		delete start3;
		
		SDL_Delay(5000);
		loadSDL->clean(); // call the clean method
		return 0;

	}catch (exception ex) {
		cout << "Exception Caught \n" << ex.what();
	}	
	return 0;

}


