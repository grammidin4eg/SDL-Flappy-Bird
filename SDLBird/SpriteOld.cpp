#include "SpriteOld.h"
#include "ResManager.h"

SpriteOld::SpriteOld(SDL_Renderer* renderer)
{
	init();
	mRenderer = renderer;
}

SpriteOld::SpriteOld(SDL_Renderer* renderer, std::string name)
{
	mRenderer = renderer;

	loadSurface(ResManager::getImg(name));
}

SpriteOld::~SpriteOld()
{
	removeImage();
	mClip = NULL;
}

void SpriteOld::draw()
{
	drawToPos(mX, mY);
}

void SpriteOld::drawToPos(int x, int y)
{
	// Прямоугольник с размерами спрайта
	SDL_Rect renderQuad = { x, y, getWidth(), getHeight()};

	if (mTexture)
	{
		SDL_RenderCopyEx(mRenderer, mTexture, mClip, &renderQuad, mAngle, NULL, mFlip);
	}

	// нарисуем прямоугольник для отладки
	// SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
	// SDL_RenderDrawRect(mRenderer, &renderQuad);
}

void SpriteOld::setClip(SDL_Rect* clip)
{
	mClip = clip;
}

int SpriteOld::getWidth()
{
	return (mClip == NULL ? mWidth : mClip->w);
}

int SpriteOld::getHeight()
{
	return (mClip == NULL ? mHeight : mClip->h);
}

void SpriteOld::setWidth(int width)
{
	mWidth = width;
}

void SpriteOld::setHeight(int height)
{
	mHeight = height;
}

void SpriteOld::setPos(int x, int y)
{
	mX = x;
	mY = y;
}

int SpriteOld::getX()
{
	return mX;
}

int SpriteOld::getY()
{
	return mY;
}

void SpriteOld::setAngle(double angle)
{
	mAngle = angle;
}

void SpriteOld::setFlip(SDL_RendererFlip flip)
{
	mFlip = flip;
}

void SpriteOld::setCheckCollision(bool check)
{
	mCheckCollision = check;
}

bool SpriteOld::isCheckCollision()
{
	return mCheckCollision;
}

bool SpriteOld::checkCollision(SpriteOld* another)
{
	if (!another->isCheckCollision())
	{
		return false;
	}
	// прямоугольник с размерами спрайта
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	// Прямоугольник 1
	leftA = mX;
	rightA = mX + getWidth();
	
	topA = mY;
	bottomA = mY + getHeight();

	// Прямоугольник 2
	leftB = another->getX();
	rightB = another->getX() + another->getWidth();

	topB = another->getY();
	bottomB = another->getY() + another->getHeight();


	return !((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB));
}

void SpriteOld::removeImage()
{
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void SpriteOld::init()
{
	mX = 0;
	mY = 0;
	mHeight = 0;
	mWidth = 0;

	mClip = NULL;
	mAngle = 0;

	mCheckCollision = false;

	mFlip = SDL_FLIP_NONE;
}

void SpriteOld::loadSurface(SDL_Surface* loadedSurface)
{
	if (loadedSurface) 
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		exceptionIfNull(mTexture, "Unable to create texture.");

		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;

		// SDL_FreeSurface(loadedSurface);
	}
}
