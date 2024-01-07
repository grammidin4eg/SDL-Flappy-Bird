#pragma once

#include <stdio.h>
#include <iostream>
#include <list>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "utils.h"
#include "SpriteOld.h"
#include "TextSprite.h"
#include "TickTimer.h"
#include "Scene.h"
#include "Sprite.h"

namespace GameObjects {

	class Window
	{
	public:
		// Создать окно
		Window(int screenWidth, int screenHeight);

		// Очистить ресурсы
		~Window();

		// Добавить сцену
		void addScene(std::string name, Scene* scene);

		// Перейти к сцене
		void gotoScene(std::string name);

		// Запустить игру
		void run();

		// Установить максимальный FPS
		void setMaxFPS(int maxFPS);

		bool isActive();

		// Вернуть Frame Per Second
		float getFPS();

		SDL_Renderer* getRenderer();

		// Создать спрайт
		Sprite* createSprite(std::string fileName);
	private:
		// список сцен
		std::unordered_map<std::string, Scene*> mSceneList;
		// текущая сцена
		Scene* mCurrentScene;

		// ширина и высота окна
		int mScreenWidth;
		int mScreenHeight;

		// ресурсы SDL
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		bool mActive;
		TickTimer mCapTimer;
		TickTimer mFpsTimer;
		int mMaxFps;
	};
}

