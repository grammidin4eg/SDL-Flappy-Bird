#pragma once
#include "SpriteOld.h"
#include "utils.h";
#include <SDL_ttf.h>
#include <SDL.h>

class TextSprite :
    public SpriteOld
{
public:
    TextSprite(TTF_Font* font, SDL_Renderer* renderer, SDL_Color textColor, std::string text) : SpriteOld(renderer)
    {
        mFont = font;
        mColor = textColor;

        SpriteOld::init();
        setText(text);
    }
    void setText(std::string text);
private:
    TTF_Font* mFont;
    SDL_Color mColor;
};

