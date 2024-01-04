
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
#include "Tube.h";
#include "GameSound.h"
#include "ResManager.h"

using namespace std;

int main(int argc, char* args[])
{
	// Константы
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const int SCREEN_FPS = 60;
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

	const int GRAVITY = 2; // гравитация, бессердечная ты...
	const int TAP_POWER = 17; // сила с которой направляемся вверх
	const float FLAP_LENGTH = 0.2f; // сек
	const float GAME_OVER_LENGTH = 2; // сек

	const float BIRD_ANGLE = 5; // Угол наклона птицы

	SDL_Renderer* renderer = NULL;
	SDL_Window* window = NULL;
	TTF_Font* fontNormal = NULL;
	TTF_Font* fontTitle = NULL;

	srand((unsigned)time(NULL));

	try {
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
		window = SDL_CreateWindow("SDL Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		exceptionIfNull(window, "Window could not be created.");

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		exceptionIfNull(renderer, "Renderer could not be created.");
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

		// Цвета
		const SDL_Color COLOR_RED = { 0xFF, 0, 0 };
		const SDL_Color COLOR_GREEN = { 0, 0xFF, 0 };
		const SDL_Color COLOR_BLUE = { 0, 0, 0xFF };
		const SDL_Color COLOR_YELLOW = { 0xFF, 0xFF, 0 };
		const SDL_Color COLOR_ORANGE = { 0xFF, 0xA5, 0 };

		// Шрифты
		fontNormal = TTF_OpenFont("fonts/LuckiestGuy.ttf", 24);
		fontTitle = TTF_OpenFont("fonts/LuckiestGuy.ttf", 54);
		
		// Загрузка ресурсов
		unique_ptr<Sprite> imgSky = make_unique<Sprite>(renderer, "SkyTileSprite.png");
		unique_ptr<TextSprite> textFps = make_unique<TextSprite>(fontNormal, renderer, COLOR_YELLOW, "Hello world");
		textFps->setPos(10, 10);

		unique_ptr<TextSprite> textTitle = make_unique<TextSprite>(fontTitle, renderer, COLOR_BLUE, "Flappy Bird");
		textTitle->setPos(SCREEN_WIDTH / 2 - textTitle->getWidth() / 2, 200);

		unique_ptr<TextSprite> textGameOver = make_unique<TextSprite>(fontTitle, renderer, COLOR_BLUE, "Game Over");
		textGameOver->setPos(SCREEN_WIDTH / 2 - textTitle->getWidth() / 2, 200);

		unique_ptr<TextSprite> textSubTitle = make_unique<TextSprite>(fontNormal, renderer, COLOR_ORANGE, "= Press SPACE to start =");
		textSubTitle->setPos(SCREEN_WIDTH / 2 - textSubTitle->getWidth() / 2, 250);

		unique_ptr<Sprite> imgBird = make_unique<Sprite>(renderer, "BirdHero.png");


		int score = 0;
		unique_ptr<TextSprite> textScore = make_unique<TextSprite>(fontNormal, renderer, COLOR_BLUE, "0");
		textScore->setPos(SCREEN_WIDTH / 2 - textScore->getWidth() / 2, 20);

		// нарезаем спрайт на несколько

		SDL_Rect flapBirdClip{ 0, 0, 50, 30 }; // машем
		SDL_Rect normalBirdClip{ 50, 0, 50, 30 }; // обычное состояние
		SDL_Rect defeatBirdClip{ 103, 0, 50, 30 }; // поражение

		imgBird->setClip(&normalBirdClip);
		imgBird->setPos(200, 250);


		unique_ptr<Sprite> imgGround = make_unique<Sprite>(renderer, "GrassThinSprite.png");

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
		bool proccess = true;
		SDL_Event event;

		TickTimer fpsTimer;
		fpsTimer.start();

		TickTimer capTimer;
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
					tubes.push_back(new Tube(renderer, SCREEN_WIDTH + i * 180, TubeOrientation::DOWN));
					tubes.push_back(new Tube(renderer, SCREEN_WIDTH + i * 180, TubeOrientation::UP));
					tubes.push_back(new Tube(renderer, SCREEN_WIDTH + i * 180, TubeOrientation::COLLIDER));
				}
			};

		genTubesFnc();

		while (proccess)
		{
			capTimer.start();
			// Проверка событий
			while (SDL_PollEvent(&event) != 0) 
			{
				if ((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE)))
				{
					proccess = false;
				}
				else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_SPACE) && keyReady) {
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
				else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_SPACE)) {
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

			SDL_RenderClear(renderer);
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
			textFps->setText("FPS: " + to_string(fpsTimer.getFPS()));
			textFps->draw();

			SDL_RenderPresent(renderer);
			capTimer.stabilizeFPS(SCREEN_TICK_PER_FRAME);
			fpsTimer.nextUpdateCycle();
		}	
		tubes.clear();
	}
	catch (logic_error& error)
	{
		printf("Error: %s. SDL Error: %s\n", error.what(), SDL_GetError());
	}

	// Очистка ресурсов
	printf("clear");

	ResManager::free();

	TTF_CloseFont(fontNormal);

	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if (window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	IMG_Quit();
	SDL_Quit();


	return 0;
}