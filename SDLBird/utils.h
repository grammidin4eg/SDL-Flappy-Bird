#pragma once

#include <stdio.h>
#include <iostream>

#include <SDL.h>

void exceptionIfNull(void* obj, const char* msg);

bool isKeyDown(SDL_Event* event, SDL_Keycode keyCode);
bool isKeyUp(SDL_Event* event, SDL_Keycode keyCode);
