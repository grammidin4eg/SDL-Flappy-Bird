#pragma once

#include <stdio.h>
#include <string>

#include "SDL.h"

class TickTimer
{
public:
	TickTimer();

	void start();
	void stop();
	bool isStarted();

	void nextUpdateCycle();

	Uint32 getTicks();

	float getFPS();

	float getSeconds();

	// стабилизировать FPS максимальным значением
	void stabilizeFPS(int screenTicksPerFrame);
private:
	Uint32 mStartTicks;
	int mCountedFrames;

	bool mStarted;
};

