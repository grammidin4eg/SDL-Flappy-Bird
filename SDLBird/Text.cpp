#include "Text.h"

namespace GameObjects {
	Text::~Text()
	{
		free();
	}
	void Text::setText(std::string text)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), mColor);
		exceptionIfNull(textSurface, "Unable to render text surface");

		mTexture = SDL_CreateTextureFromSurface(getRenderer(), textSurface);
		exceptionIfNull(mTexture, "Unable to create texture.");

		setWidth(textSurface->w);
		setHeight(textSurface->h);
	}
	void Text::start()
	{
	}
	void Text::update()
	{
	}
	void Text::draw()
	{
		SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };

		if (mTexture)
		{
			SDL_RenderCopyEx(getRenderer(), mTexture, NULL, &renderQuad, 0, NULL, SDL_FLIP_NONE);
		}
	}
	void Text::free()
	{
	}
}
