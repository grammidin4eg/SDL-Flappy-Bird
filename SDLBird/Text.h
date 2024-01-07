#pragma once
#include <string>
#include "Object.h"
#include <SDL_ttf.h>

namespace GameObjects {
    class Text :
        public Object
    {
    public:
        Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color textColor, std::string text) : Object(renderer)
        {
            mFont = font;
            mColor = textColor;
            setText(text);
        }

        ~Text();

        void setText(std::string text);

        virtual void start();
        virtual void update();
        virtual void draw();
        virtual void free();
    private:
        TTF_Font* mFont;
        SDL_Color mColor;
        SDL_Texture* mTexture;
    };
}

