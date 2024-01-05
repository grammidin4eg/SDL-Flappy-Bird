#include "SDLGameWindow.h"
#include "ResManager.h"

using namespace std;

const int MAX_SCREEN_FPS = 60;

SDLGameWindow::SDLGameWindow(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mActive = true;

	mMaxFps = MAX_SCREEN_FPS;

	// Инициализация библиотек
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw logic_error("SDL could not init.");
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw logic_error("Mixer could not init.");
	}

	// Инициализация окна
	mWindow = SDL_CreateWindow("SDL Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN);
	exceptionIfNull(mWindow, "Window could not be created.");

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	exceptionIfNull(mRenderer, "Renderer could not be created.");
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);

	mFpsTimer.start();
}

SDLGameWindow::~SDLGameWindow()
{
	ResManager::free();

	for (auto iter = mSpriteList.begin(); iter != mSpriteList.end(); iter++)
	{
		(*iter)->removeImage();
	}

	if (mRenderer != NULL) {
		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;
	}

	if (mWindow != NULL)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;
	}

	IMG_Quit();
	SDL_Quit();
}

Sprite* SDLGameWindow::createSprite(std::string resName)
{
	Sprite* newSprite = new Sprite(mRenderer, resName);
	addSprite(newSprite);
	return newSprite;
}

TextSprite* SDLGameWindow::createTextSprite(std::string resName, TTF_Font* font, SDL_Color textColor)
{
	TextSprite* newSprite = new TextSprite(font, mRenderer, textColor, resName);
	addSprite(newSprite);
	return newSprite;
}

Sprite* SDLGameWindow::addSprite(Sprite* newSprite)
{
	mSpriteList.push_back(newSprite);
	return newSprite;
}

void SDLGameWindow::setMaxFPS(int maxFPS)
{
	mMaxFps = maxFPS;
}

bool SDLGameWindow::isActive()
{
	return mActive;
}

void SDLGameWindow::dropWindow()
{
	mActive = false;
}

bool SDLGameWindow::haveEvents(SDL_Event* event)
{
	bool hasEvent = (SDL_PollEvent(event) != 0);
	if (event->type == SDL_QUIT)
	{
		dropWindow();
		hasEvent = false;
	}
	return hasEvent;
}

void SDLGameWindow::renderClear()
{
	SDL_RenderClear(mRenderer);
}

void SDLGameWindow::renderPresent()
{
	SDL_RenderPresent(mRenderer);
}

void SDLGameWindow::startCycle()
{
	mCapTimer.start();
}

void SDLGameWindow::finishCycle()
{
	renderPresent();
	mCapTimer.stabilizeFPS(1000 / mMaxFps);
	mFpsTimer.nextUpdateCycle();
}

float SDLGameWindow::getFPS()
{
	return mFpsTimer.getFPS();
}
