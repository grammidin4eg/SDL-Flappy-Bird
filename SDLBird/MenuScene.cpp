#include "MenuScene.h"
#include "Sprite.h"
#include "FpsText.h"

void MenuScene::onInit(SDL_Renderer* renderer, SDL_Rect winSize)
{
	GameObjects::Sprite* background = new GameObjects::Sprite(renderer, "background.png");

	background->setWidth(winSize.w);
	background->setHeight(winSize.h);

	addObject(background);

	addObject(new FpsText(renderer));
}

void MenuScene::onStart(SDL_Renderer* renderer, SDL_Rect winSize)
{
}
