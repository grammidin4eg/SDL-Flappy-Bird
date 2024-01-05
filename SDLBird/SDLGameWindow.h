#pragma once

#include <stdio.h>
#include <iostream>
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "utils.h"
#include "Sprite.h"
#include "TextSprite.h"
#include "TickTimer.h"

class SDLGameWindow
{
public:
	SDLGameWindow(int screenWidth, int screenHeight);
	~SDLGameWindow();
    Sprite* createSprite(std::string resName);
	TextSprite* createTextSprite(std::string resName, TTF_Font* font, SDL_Color textColor);
	Sprite* addSprite(Sprite* newSprite);

	void setMaxFPS(int maxFPS);

	bool isActive();
	void dropWindow();

	bool haveEvents(SDL_Event* event);

	void renderClear();
	void renderPresent();

	void startCycle();
	void finishCycle();

	float getFPS();
private:
	int mScreenWidth;
	int mScreenHeight;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mActive;
	std::list<Sprite*> mSpriteList;
	TickTimer mCapTimer;
	TickTimer mFpsTimer;
	int mMaxFps;
};

