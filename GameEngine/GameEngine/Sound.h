#pragma once
#include <SDL_mixer.h>
#include <Windows.h>
class Sound
{
public:
	Sound(const char* path);
	~Sound();
	Mix_Chunk* wave();
	Mix_Music* music();
	

private:
	Mix_Chunk* m_wave;
	Mix_Music* m_music;
};