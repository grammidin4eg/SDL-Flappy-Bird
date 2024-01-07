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
		// ������� ����
		Window(int screenWidth, int screenHeight);

		// �������� �������
		~Window();

		// �������� �����
		void addScene(std::string name, Scene* scene);

		// ������� � �����
		void gotoScene(std::string name);

		// ��������� ����
		void run();

		// ���������� ������������ FPS
		void setMaxFPS(int maxFPS);

		bool isActive();

		// ������� Frame Per Second
		float getFPS();

		SDL_Renderer* getRenderer();

		// ������� ������
		Sprite* createSprite(std::string fileName);
	private:
		// ������ ����
		std::unordered_map<std::string, Scene*> mSceneList;
		// ������� �����
		Scene* mCurrentScene;

		// ������ � ������ ����
		int mScreenWidth;
		int mScreenHeight;

		// ������� SDL
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		bool mActive;
		TickTimer mCapTimer;
		TickTimer mFpsTimer;
		int mMaxFps;
	};
}

