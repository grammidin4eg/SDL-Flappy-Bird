#include "Sprite.h"
#include "ResManager.h"

Sprite::Sprite(SDL_Renderer* renderer)
{
	init();
	mRenderer = renderer;
}

Sprite::Sprite(SDL_Renderer* renderer, std::string name)
{
	mRenderer = renderer;

	loadSurface(ResManager::getImg(name));
}

Sprite::~Sprite()
{
	removeImage();
	mClip = NULL;
}

void Sprite::draw()
{
	drawToPos(mX, mY);
}

void Sprite::drawToPos(int x, int y)
{
	// Прямоугольник с размерами спрайта
	SDL_Rect renderQuad = { x, y, getWidth(), getHeight()};

	// Обрезаем, если надо
	/*if (mClip != NULL)
	{
		renderQuad.w = mClip->w;
		renderQuad.h = mClip->h;
	}*/

	if (mTexture)
	{
		SDL_RenderCopyEx(mRenderer, mTexture, mClip, &renderQuad, mAngle, NULL, mFlip);
	}

	// нарисуем прямоугольник для отладки
	// SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
	// SDL_RenderDrawRect(mRenderer, &renderQuad);
}

void Sprite::setClip(SDL_Rect* clip)
{
	mClip = clip;
}

int Sprite::getWidth()
{
	return (mClip == NULL ? mWidth : mClip->w);
}

int Sprite::getHeight()
{
	return (mClip == NULL ? mHeight : mClip->h);
}

void Sprite::setWidth(int width)
{
	mWidth = width;
}

void Sprite::setHeight(int height)
{
	mHeight = height;
}

void Sprite::setPos(int x, int y)
{
	mX = x;
	mY = y;
}

int Sprite::getX()
{
	return mX;
}

int Sprite::getY()
{
	return mY;
}

void Sprite::setAngle(double angle)
{
	mAngle = angle;
}

void Sprite::setFlip(SDL_RendererFlip flip)
{
	mFlip = flip;
}

void Sprite::setCheckCollision(bool check)
{
	mCheckCollision = check;
}

bool Sprite::isCheckCollision()
{
	return mCheckCollision;
}

bool Sprite::checkCollision(Sprite* another)
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

void Sprite::removeImage()
{
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Sprite::init()
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

void Sprite::loadSurface(SDL_Surface* loadedSurface)
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
