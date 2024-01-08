#pragma once
#include "Text.h"
#include "ResManager.h"
#include "Colors.h"
class FpsText :
    public GameObjects::Text
{
public:
    FpsText(SDL_Renderer* renderer) : GameObjects::Text(renderer, 
        ResManager::getFont("LuckiestGuy.ttf", 24), GameObjects::COLOR_YELLOW, "0")
    {
        setPos(10, 10);
    }

    virtual void update();
};

