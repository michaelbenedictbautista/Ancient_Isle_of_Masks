#include "Sound.h"
#include <iostream>

using namespace std;

// constructor
Sound::Sound(const char* path)
{
	// Verify and load wave file and mp3
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	m_wave = Mix_LoadWAV(path);
	if (m_wave == nullptr) {
		cout << "Mp3 not found" << endl;
	}

	m_music = Mix_LoadMUS(path);
	if (m_music == nullptr) {
		cout << "Mp3 not found" << endl;
	}
}

// destructor
Sound:: ~Sound()
{
}

// getters
Mix_Chunk* Sound::wave()
{
	return m_wave;
}
Mix_Music* Sound::music()
{
	return m_music;
}

