#include "SDLGameWindow.h"
#include "ResManager.h"

using namespace std;
namespace GameObjects {
	const int MAX_SCREEN_FPS = 60;

	Window::Window(int screenWidth, int screenHeight)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;
		mActive = true;

		mMaxFps = MAX_SCREEN_FPS;

		mCurrentScene = NULL;

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

	Window::~Window()
	{
		// очистить ресурсы менеджера
		ResManager::free();

		// вызвать деструктор всех добавленных сцен
		for (const pair<string, Scene*>& tup : mSceneList)
		{
			(tup.second)->~Scene();
		}

		mSceneList.clear();

		// Удалить ресурсы SDL
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

	void Window::addScene(std::string name, Scene* scene)
	{
		scene->onInit(mRenderer, SDL_Rect {0, 0, mScreenWidth, mScreenHeight});
		mSceneList.insert(make_pair(name, scene));
		if (mCurrentScene == NULL) {
			mCurrentScene = scene;
		}
	}

	void Window::gotoScene(std::string name)
	{
		auto findedScene = mSceneList.find(name);
		if (findedScene != mSceneList.end())
		{
			mCurrentScene = findedScene->second;
			mCurrentScene->start();
		}
	}

	void Window::run()
	{
		mCurrentScene->start();
		while (this->isActive())
		{
			mCapTimer.start();
			// Проверка событий
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT) {
					mActive = false;
				}
			}

			// Обновление сцены
			mCurrentScene->update();

			// Отрисовка
			SDL_RenderClear(mRenderer);
			
			mCurrentScene->draw();

			SDL_RenderPresent(mRenderer);
			mCapTimer.stabilizeFPS(1000 / mMaxFps);
			mFpsTimer.nextUpdateCycle();
		}
	}

	void Window::setMaxFPS(int maxFPS)
	{
		mMaxFps = maxFPS;
	}

	bool Window::isActive()
	{
		return mActive;
	}

	float Window::getFPS()
	{
		return mFpsTimer.getFPS();
	}
	SDL_Renderer* Window::getRenderer()
	{
		return mRenderer;
	}
	Sprite* Window::createSprite(std::string fileName)
	{
		return new Sprite(mRenderer, fileName);
	}
	Text* Window::createText(TTF_Font* font, SDL_Color textColor, std::string text)
	{
		return new Text(mRenderer, font, textColor, text);
	}
}
