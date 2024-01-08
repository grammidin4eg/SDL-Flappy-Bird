
#include <stdio.h>
#include <iostream>
#include <list>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "utils.h"
#include "SpriteOld.h"
#include "TextSprite.h"
#include "TickTimer.h"
#include "Tube.h";
#include "GameSound.h"
#include "ResManager.h"

#include "SDLGameWindow.h"
#include "Colors.h"
#include "Scene.h"
#include "Sprite.h"
#include "Text.h"

#include "MenuScene.h"

using namespace std;

int main(int argc, char* args[])
{
	// Константы
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 960;

	const int GRAVITY = 2; // гравитация, бессердечная ты...
	const int TAP_POWER = 17; // сила с которой направляемся вверх
	const float FLAP_LENGTH = 0.2f; // сек
	const float GAME_OVER_LENGTH = 2; // сек

	const float BIRD_ANGLE = 5; // Угол наклона птицы

	TTF_Font* fontNormal = NULL;
	TTF_Font* fontTitle = NULL;

	srand((unsigned)time(NULL));

	try {
		GameObjects::Window window(SCREEN_WIDTH, SCREEN_HEIGHT);

		/*

		GameObjects::Text* fpsText = window.createText(ResManager::getFont("LuckiestGuy.ttf", 24), GameObjects::COLOR_YELLOW, "0");
		fpsText->setPos(10, 10);

		menu->addObject(background);
		menu->addObject(fpsText);*/

		window.addScene("menu", new MenuScene());

		window.run();

		// лямбда? классы?
		// лямбда на старт и на апдейт

		/*
		// Шрифты
		fontNormal = ResManager::getFont("LuckiestGuy.ttf", 24);
		fontTitle = ResManager::getFont("LuckiestGuy.ttf", 54);
		
		// Загрузка ресурсов
		Sprite* imgSky = window.createSprite("SkyTileSprite.png");
		TextSprite* textFps = window.createTextSprite("Hello world", fontNormal, COLOR_YELLOW);
		textFps->setPos(10, 10);

		TextSprite* textTitle = window.createTextSprite("Flappy Bird", fontTitle, COLOR_BLUE);
		textTitle->setPos(SCREEN_WIDTH / 2 - textTitle->getWidth() / 2, 200);

		TextSprite* textGameOver = window.createTextSprite("Game Over", fontTitle, COLOR_BLUE);
		textGameOver->setPos(SCREEN_WIDTH / 2 - textTitle->getWidth() / 2, 200);

		TextSprite* textSubTitle = window.createTextSprite("= Press SPACE to start =", fontNormal, COLOR_ORANGE);
		textSubTitle->setPos(SCREEN_WIDTH / 2 - textSubTitle->getWidth() / 2, 250);

		Sprite* imgBird = window.createSprite("BirdHero.png");


		int score = 0;
		TextSprite* textScore = window.createTextSprite("0", fontNormal, COLOR_BLUE);
		textScore->setPos(SCREEN_WIDTH / 2 - textScore->getWidth() / 2, 20);

		// нарезаем спрайт на несколько

		SDL_Rect flapBirdClip{ 0, 0, 50, 30 }; // машем
		SDL_Rect normalBirdClip{ 50, 0, 50, 30 }; // обычное состояние
		SDL_Rect defeatBirdClip{ 103, 0, 50, 30 }; // поражение

		imgBird->setClip(&normalBirdClip);
		imgBird->setPos(200, 250);


		Sprite* imgGround = window.createSprite("GrassThinSprite.png");

		// музыка и звуки
		unique_ptr<GameMusic> sndTitle = make_unique<GameMusic>("Title.mp3");
		sndTitle->play();

		unique_ptr<GameMusic> sndGame = make_unique<GameMusic>("Game.mp3");
		unique_ptr<GameMusic> sndGameOver = make_unique<GameMusic>("GameOver.mp3");

		unique_ptr<GameSound> sndHit = make_unique<GameSound>("hit.wav");
		unique_ptr<GameSound> sndFlap = make_unique<GameSound>("flap.wav");
		unique_ptr<GameSound> sndBonus = make_unique<GameSound>("Bonus.mp3");


		// Состояние игры
		enum class GameState { Menu, Game, GameOver };
		GameState curGameState{ GameState::Menu };
		// Цикл игры

		SDL_Event event;
		TickTimer flapTimer;

		bool keyReady = true;

		//вектор импульса
		int birdVelocity = 0;

		float scrollingOffset = 0;

		list<Tube*> tubes;


		// функции
		auto gameOverFnc = [&]()
		{
			sndGame->stop();
			sndHit->play();
			sndGameOver->play(1);
			imgBird->setClip(&defeatBirdClip);
			curGameState = GameState::GameOver;
			flapTimer.start();
		};

		auto genTubesFnc = [&]()
			{
				if (tubes.size() > 0)
				{
					tubes.clear();
				}
				for (int i = 0; i < 4; i++)
				{
					// TODO: 
					// tubes.push_back(new Tube(renderer, SCREEN_WIDTH + i * 180, TubeOrientation::DOWN));
					// tubes.push_back(new Tube(renderer, SCREEN_WIDTH + i * 180, TubeOrientation::UP));
					// tubes.push_back(new Tube(renderer, SCREEN_WIDTH + i * 180, TubeOrientation::COLLIDER));
				}
			};

		genTubesFnc();

		while (window.isActive())
		{
			window.startCycle();
			// Проверка событий
			while (window.haveEvents(&event)) 
			{
				if (isKeyDown(&event, SDLK_ESCAPE))
				{
					window.dropWindow();
				}
				else if (isKeyDown(&event, SDLK_SPACE) && keyReady) {
					keyReady = false;
					switch (curGameState)
					{
					case GameState::Menu:
						curGameState = GameState::Game;
						sndTitle->stop();
						sndGame->play();
						break;
					case GameState::Game:
						// птице дать импульс
						birdVelocity = -TAP_POWER;
						imgBird->setClip(&flapBirdClip);
						imgBird->setAngle(-BIRD_ANGLE);
						flapTimer.start();
						sndFlap->play();
						break;
					case GameState::GameOver:
						if (flapTimer.getSeconds() > GAME_OVER_LENGTH) {
							score = 0;
							textScore->setText("0");
							sndGameOver->stop();
							sndGame->play();
							flapTimer.stop();
							imgBird->setClip(&normalBirdClip);
							imgBird->setPos(200, 250);
							genTubesFnc();
							curGameState = GameState::Game;
						}
						break;
					}
				}
				else if (isKeyUp(&event, SDLK_SPACE)) {
					keyReady = true;
				}
			}

			// Обновление сцены
			if (curGameState == GameState::Game)
			{
				// смещение фона
				scrollingOffset--;
				if (scrollingOffset < -imgGround->getWidth())
				{
					scrollingOffset = 0;
				}
				// перемещение птицы
				if (birdVelocity < GRAVITY) {
					birdVelocity += GRAVITY;
				}
				imgBird->setPos(imgBird->getX(), imgBird->getY() + birdVelocity);

				if (imgBird->getY() < 0)
				{
					imgBird->setPos(imgBird->getX(), 0);
				}

				// проверяем падение на землю
				if (imgBird->getY() > SCREEN_HEIGHT - imgGround->getHeight() - 5)
				{
					gameOverFnc();
				}

				if (flapTimer.getSeconds() > FLAP_LENGTH)
				{
					flapTimer.stop();
					imgBird->setClip(&normalBirdClip);
					imgBird->setAngle(BIRD_ANGLE);
				}

				// обновление положения труб
				for (auto iter = tubes.begin(); iter != tubes.end(); iter++)
				{ 
					(*iter)->updateScrolling();
					// проверка на столкновение с птицей
					if (imgBird->checkCollision((*iter)))
					{
						if ((*iter)->isOrientation(TubeOrientation::COLLIDER))
						{
							// пролетели между, добавляем бонус
							(*iter)->setCheckCollision(false);
							score++;
							textScore->setText(to_string(score));
							sndBonus->play();
						}
						else 
						{
							// столкновение с трубой
							gameOverFnc();
						}
					}
				}


			}


			// Отрисовка
			window.renderClear();
			imgSky->draw();

			switch (curGameState)
			{
			case GameState::Menu:
				textTitle->draw();
				textSubTitle->draw();
				break;
			case GameState::Game:
				imgBird->draw();
				for (auto iter = tubes.begin(); iter != tubes.end(); iter++)
				{
					(*iter)->draw();
				}
				textScore->draw();
				break;
			case GameState::GameOver:
				textGameOver->draw();
				if (flapTimer.getSeconds() > GAME_OVER_LENGTH)
				{
					textSubTitle->draw();
				}
				imgBird->draw();
				textScore->draw();
				break;
			}

			imgGround->drawToPos(scrollingOffset, SCREEN_HEIGHT - imgGround->getHeight());
			imgGround->drawToPos(scrollingOffset + imgGround->getWidth(), SCREEN_HEIGHT - imgGround->getHeight());
			textFps->setText("FPS: " + to_string(window.getFPS()));
			textFps->draw();

			window.finishCycle();
		}	
		tubes.clear();
		*/
	}
	catch (logic_error& error)
	{
		printf("Error: %s. SDL Error: %s\n", error.what(), SDL_GetError());
	}

	return 0;
}