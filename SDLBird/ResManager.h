#pragma once
#include <map>
#include <unordered_map>
#include <iostream>
#include <cassert>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "utils.h"


using namespace std;

class ResManager
{
private:
	ResManager() {}
	unordered_map<string, SDL_Surface*> mResSurfaces;
	unordered_map<string, TTF_Font*> mResFonts;
	static ResManager* instancePtr;

public:
	static ResManager* getInstance();

	static SDL_Surface* getImg(string name);

	static TTF_Font* getFont(string name, int size);

	static void free();
};

