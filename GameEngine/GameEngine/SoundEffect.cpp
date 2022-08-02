#include "SoundEffect.h"

#pragma comment(lib, "winmm.lib")

void SoundEffect::playMusic() {
	PlaySound(TEXT("assets/attackSoundEffect.wav"), NULL, SND_ASYNC);
}

void SoundEffect::stopMusic() {
	PlaySound(NULL, 0, 0);
}

