#include "utils.h"

void exceptionIfNull(void* obj, const char* msg)
{
	if (obj == NULL) {
		throw std::logic_error(msg);
	}
}

bool isKeyDown(SDL_Event* event, SDL_Keycode keyCode)
{
	return ((event->type == SDL_KEYDOWN) && (event->key.keysym.sym == keyCode));
}

bool isKeyUp(SDL_Event* event, SDL_Keycode keyCode)
{
	return ((event->type == SDL_KEYUP) && (event->key.keysym.sym == keyCode));
}

