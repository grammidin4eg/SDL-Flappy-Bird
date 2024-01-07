#pragma once
#include "Object.h"
#include <string>

#include <SDL_image.h>
#include "ResManager.h"

namespace GameObjects {
    class Sprite :
        public Object
    {
    public:
        Sprite(SDL_Renderer* renderer, std::string fileName) : Object(renderer)
        {
            mClip = NULL;
            mAngle = 0;
            mFlip = SDL_FLIP_NONE;
            loadSurface(ResManager::getImg(fileName));
        }
        ~Sprite();

        virtual void start();
        virtual void update();
        virtual void draw();
        virtual void free();

        int getWidth();
        int getHeight();

        int getOriginalWidth();
        int getOriginalHeight();

        // установить область, которую рисуем из текстуры
        void setClip(SDL_Rect* clip);

        // установить угол поворота
        void setAngle(double angle);

        // установить отзеркаливание
        void setFlip(SDL_RendererFlip flip);

        void loadSurface(SDL_Surface* loadedSurface);
    private:
        // область, которую рисуем из спрайта
        SDL_Rect* mClip;

        // угол поворота
        double mAngle;
        SDL_RendererFlip mFlip;

        SDL_Texture* mTexture;

        int mOriginalWidth;
        int mOriginalHeight;
    };
}

