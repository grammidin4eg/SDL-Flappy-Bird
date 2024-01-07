#pragma once
#include "SpriteOld.h"

enum class TubeOrientation { UP, DOWN, COLLIDER };

class Tube :
    public SpriteOld
{
public:
    Tube(SDL_Renderer* renderer, int startPos, TubeOrientation orientation) : SpriteOld(renderer, "ColumnSprite.png")
    {
        mStartPos = startPos;
        mOrientation = orientation;
        if (orientation == TubeOrientation::COLLIDER)
        {
            setHeight(600);
            SpriteOld::removeImage();
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

