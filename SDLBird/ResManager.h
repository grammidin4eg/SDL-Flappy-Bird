#pragma once
#include <map>
#include <unordered_map>
#include <iostream>
#include <cassert>

#include <SDL.h>
#include <SDL_image.h>

#include "utils.h"


using namespace std;

class ResManager
{
private:
	ResManager() {}
	unordered_map<string, SDL_Surface*> mRes;
	static ResManager* instancePtr;

public:
	static ResManager* getInstance();

	static SDL_Surface* getImg(string name);

	static void free();
};

