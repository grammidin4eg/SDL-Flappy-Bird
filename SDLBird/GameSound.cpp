#include "GameSound.h"

GameSound::GameSound(std::string name)
{
	std::string path = "sound/" + name;
	mSound = Mix_LoadWAV(path.c_str());
	exceptionIfNull(mSound, "Failed to load sound file.");
}

GameSound::~GameSound()
{
	Mix_FreeChunk(mSound);
	mSound = NULL;
}

void GameSound::play(int loops)
{
	Mix_PlayChannel(-1, mSound, loops);
}

GameMusic::GameMusic(std::string name)
{
	std::string path = "sound/" + name;
	mSound = Mix_LoadMUS(path.c_str());
	exceptionIfNull(mSound, "Failed to load sound file.");
}

GameMusic::~GameMusic()
{
	Mix_FreeMusic(mSound);
	mSound = NULL;
}

void GameMusic::play(int loops)
{
	Mix_PlayMusic(mSound, loops);
}

void GameMusic::pause()
{
	Mix_PausedMusic();
}

void GameMusic::resume()
{
	Mix_ResumeMusic();
}

void GameMusic::stop()
{
	Mix_HaltMusic();
}

bool GameMusic::isPlaying()
{
	return (Mix_PlayingMusic() != 0);
}

bool GameMusic::isPaused()
{
	return (Mix_PausedMusic() == 1);
}
