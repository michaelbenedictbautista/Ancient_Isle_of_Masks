#include "SoundEffect.h"

#pragma comment(lib, "winmm.lib")

// function definition for playing music with location, null repetition and asycnhronous setting.
void SoundEffect::playMusic() {
	PlaySound(TEXT("assets/attackSoundEffect.wav"), NULL, SND_ASYNC);
}

// function to stop music
void SoundEffect::stopMusic() {
	PlaySound(NULL, 0, 0);
}

