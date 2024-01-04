#pragma once

#include <SDL_mixer.h>
#include "utils.h"

class GameSound
{
public:
	GameSound(std::string name);
	~GameSound();
	void play(int loops = 0);
private:
	Mix_Chunk* mSound;
};


class GameMusic
{
public:
	GameMusic(std::string name);
	~GameMusic();

	void play(int loops = 0);
	void pause();
	void resume();
	void stop();

	bool isPlaying();
	bool isPaused();
private:
	Mix_Music* mSound;
};

