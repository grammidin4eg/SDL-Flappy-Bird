#include "Tube.h"

void Tube::updateScrolling()
{
	mX--;
	if (mX < -getWidth())
	{
		resetPos();
	}
}

void Tube::resetPos()
{
	mX = mStartPos;
	SpriteOld::setCheckCollision(true);
	if (mOrientation != TubeOrientation::COLLIDER)
	{
		int orient = mOrientation == TubeOrientation::DOWN ? 280 : -200;
		mY = orient + (rand() % 161);
		SDL_RendererFlip flip = mOrientation == TubeOrientation::DOWN ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;
		SpriteOld::setFlip(flip);
	}
}

bool Tube::isOrientation(TubeOrientation orientation)
{
	return orientation == mOrientation;
}
