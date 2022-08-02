#include "Sound.h"

Sound::Sound(const char* path)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	m_wave = Mix_LoadWAV(path);

	if (m_wave == nullptr) {
		exit(1);
	}

	m_music = Mix_LoadMUS(path);
	if (m_music == nullptr) {
		exit(1);
	}

}

Sound:: ~Sound()
{
}

Mix_Chunk* Sound::wave()
{
	return m_wave;
}
Mix_Music* Sound::music()
{
	return m_music;
}

