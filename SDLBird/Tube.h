#pragma once
#include "Sprite.h"

enum class TubeOrientation { UP, DOWN, COLLIDER };

class Tube :
    public Sprite
{
public:
    Tube(SDL_Renderer* renderer, int startPos, TubeOrientation orientation) : Sprite(renderer, "ColumnSprite.png")
    {
        mStartPos = startPos;
        mOrientation = orientation;
        if (orientation == TubeOrientation::COLLIDER)
        {
            setHeight(600);
            Sprite::removeImage();
        }
        resetPos();
    }

    void updateScrolling();
    void resetPos();
    bool isOrientation(TubeOrientation orientation);
private:
    int mStartPos;
    TubeOrientation mOrientation;
};

