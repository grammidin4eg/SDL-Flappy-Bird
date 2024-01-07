#include "TextSprite.h"

void TextSprite::setText(std::string text)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, text.c_str(), mColor);
	exceptionIfNull(textSurface, "Unable to render text surface");

	SpriteOld::loadSurface(textSurface);
}
