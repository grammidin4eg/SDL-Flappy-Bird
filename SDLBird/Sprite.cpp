#include "Sprite.h"
namespace GameObjects {
	Sprite::~Sprite()
	{
		free();
	}
	void Sprite::update()
	{
	}
	void Sprite::draw()
	{
		// Прямоугольник с размерами спрайта
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight()};

		if (mTexture)
		{
			SDL_RenderCopyEx(getRenderer(), mTexture, mClip, &renderQuad, mAngle, NULL, mFlip);
		}

		// нарисуем прямоугольник для отладки
		// SDL_SetRenderDrawColor(mRenderer, 0x00, 0xFF, 0x00, 0xFF);
		// SDL_RenderDrawRect(mRenderer, &renderQuad);
	}
	void Sprite::free()
	{
		if (mTexture)
		{
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
		}
	}
	int Sprite::getWidth()
	{
		return (mClip == NULL ? Object::getWidth() : mClip->w);
	}
	int Sprite::getHeight()
	{
		return (mClip == NULL ? Object::getHeight() : mClip->h);
	}
	void Sprite::setClip(SDL_Rect* clip)
	{
		mClip = clip;
	}
	void Sprite::setAngle(double angle)
	{
		mAngle = angle;
	}
	void Sprite::setFlip(SDL_RendererFlip flip)
	{
		mFlip = flip;
	}
	void Sprite::loadSurface(SDL_Surface* loadedSurface)
	{
		if (loadedSurface)
		{
			mTexture = SDL_CreateTextureFromSurface(getRenderer(), loadedSurface);
			exceptionIfNull(mTexture, "Unable to create texture.");

			setWidth(loadedSurface->w);
			setHeight(loadedSurface->h);
		}
	}
}