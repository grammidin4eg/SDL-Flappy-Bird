#pragma once
#include "Sprite.h"
#include "utils.h";
#include <SDL_ttf.h>
#include <SDL.h>

class TextSprite :
    public Sprite
{
public:
    TextSprite(TTF_Font* font, SDL_Renderer* renderer, SDL_Color textColor, std::string text) : Sprite(renderer)
    {
        mFont = font;
        mColor = textColor;

        Sprite::init();
        setText(text);
    }
    void setText(std::string text);
private:
    TTF_Font* mFont;
    SDL_Color mColor;
};

