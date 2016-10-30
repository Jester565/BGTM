#pragma once
#include <string>
#include <SDL_mixer.h>
#include <iostream>

class Sound
{
public:
	Sound(char* path);
	Sound(char* path, double volScale);
	static void pauseAll();
	static void resumeAll();
	void play();
	void pause();
	void resume();
	void halt();
	void stopResetPlay();
	void destroy();
	void setVolume(double scale);
	bool playing();
	static void setMusic(char* path);
	static void musicPlay();
	static void musicPause();
	static void musicResume();
	static void musicHalt();
	static void musicStopResetPlay();
	static void musicDestroy();
	static bool musicPlaying();
	static void musicSetVolume(double scale);
	~Sound();
private:
	int channel = -1;
	Mix_Chunk* soundChunk = NULL;
	static Mix_Music* music;
};

inline void Sound::setVolume(double scale)
{
	Mix_VolumeChunk(soundChunk, (int)(scale * 128));
}

inline void Sound::pause()
{
	Mix_Pause(channel);
}

inline void Sound::resume()
{
	Mix_Resume(channel);
}

inline void Sound::stopResetPlay()
{
	halt();
	play();
}

inline void Sound::halt()
{
	Mix_HaltChannel(channel);
}

inline void Sound::pauseAll()
{
	Mix_Pause(-1);
}

inline void Sound::resumeAll()
{
	Mix_Resume(-1);
}

inline void Sound::destroy()
{
	Mix_FreeChunk(soundChunk);
	soundChunk = NULL;
}

inline void Sound::play()
{
	channel = Mix_PlayChannel(-1, soundChunk, 0);
	if (channel == -1)
	{
		std::cout << "Error playing sound! Mix_Error: " << Mix_GetError << std::endl;
	}
}

inline bool Sound::playing()
{
	Mix_Playing(channel);
}

inline void Sound::setMusic(char* path)
{
	if (music != NULL)
	{
		musicDestroy();
	}
	music = Mix_LoadMUS(path);
}

inline void Sound::musicSetVolume(double scale)
{
	Mix_VolumeMusic((int)(scale * 128));
}

inline void Sound::musicPause()
{
	Mix_PauseMusic();
}

inline void Sound::musicResume()
{
	Mix_ResumeMusic();
}

inline void Sound::musicStopResetPlay()
{
	musicHalt();
	musicPlay();
}

inline void Sound::musicHalt()
{
	Mix_HaltMusic();
}

inline void Sound::musicDestroy()
{
	if (music != NULL)
	{
		Mix_FreeMusic(music);
		music = NULL;
	}
}

inline void Sound::musicPlay()
{
	Mix_PlayMusic(music, 0);
}

inline bool Sound::musicPlaying()
{
	return Mix_PlayingMusic();
}