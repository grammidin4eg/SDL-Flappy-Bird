#pragma once
#include "Scene.h"
class MenuScene :
    public GameObjects::Scene
{
    virtual void onInit(SDL_Renderer* renderer, SDL_Rect winSize);

    virtual void onStart(SDL_Renderer* renderer, SDL_Rect winSize);
};

