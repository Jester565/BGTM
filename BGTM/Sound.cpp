#include "Sound.h"

Sound::Sound(char* path)
{
	soundChunk = Mix_LoadWAV(path);
}

Sound::Sound(char* path, double volScale)
{
	soundChunk = Mix_LoadWAV(path);
	setVolume(volScale);
}

Mix_Music* Sound::music = NULL;

Sound::~Sound()
{
	Mix_FreeChunk(soundChunk);
	soundChunk = NULL;
}
