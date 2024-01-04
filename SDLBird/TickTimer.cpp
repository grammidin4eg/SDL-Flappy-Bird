#include "TickTimer.h"

TickTimer::TickTimer()
{
	mStartTicks = 0;
	mCountedFrames = 0;

	mStarted = false;
}

void TickTimer::start()
{
	mStarted = true;
	mStartTicks = SDL_GetTicks();
	mCountedFrames = 0;
}

void TickTimer::stop()
{
	mStarted = false;
}

bool TickTimer::isStarted()
{
	return mStarted;
}

void TickTimer::nextUpdateCycle()
{
	if (mStarted)
	{
		mCountedFrames++;
	}
}

Uint32 TickTimer::getTicks()
{
	if (mStarted)
	{
		return SDL_GetTicks() - mStartTicks;
	}
	return 0;
}

float TickTimer::getFPS()
{
	float avgFPS = mCountedFrames / (getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}
	return avgFPS;
}

float TickTimer::getSeconds()
{
	return (getTicks() / 1000.f);
}

void TickTimer::stabilizeFPS(int screenTicksPerFrame)
{
	int frameTicks = getTicks();
	if (frameTicks < screenTicksPerFrame)
	{
		SDL_Delay(screenTicksPerFrame - frameTicks);
	}
}


