#include "ResManager.h"

ResManager* ResManager::getInstance()
{
	if (instancePtr == NULL)
	{
		instancePtr = new ResManager();
	}
	return instancePtr;
}

SDL_Surface* ResManager::getImg(string name)
{
	unordered_map<string, SDL_Surface*>* res = &getInstance()->mResSurfaces;
	auto findedRes = res->find(name);
	if (findedRes != res->end())
	{
		return findedRes->second;
	}
	else
	{
		string path = "images/" + name;
		SDL_Surface* loadedImg = IMG_Load(path.c_str());
		GameObjects::exceptionIfNull(loadedImg, "Unable to load image");
		res->insert(make_pair(name, loadedImg));
		// printf("load: %s\n", name.c_str());
		return loadedImg;
	}
}

TTF_Font* ResManager::getFont(string name, int size)
{
	unordered_map<string, TTF_Font*>* res = &getInstance()->mResFonts;
	string key = name + "::" + to_string(size);
	auto findedRes = res->find(key);
	if (findedRes != res->end())
	{
		return findedRes->second;
	}
	else
	{
		string path = "fonts/" + name;
		TTF_Font* newFont = TTF_OpenFont(path.c_str(), size);
		GameObjects::exceptionIfNull(newFont, "Unable to load font");
		res->insert(make_pair(key, newFont));
		return newFont;
	}
}

void ResManager::free()
{
	unordered_map<string, SDL_Surface*>* res = &getInstance()->mResSurfaces;
	for (const pair<string, SDL_Surface*>& tup : *res)
	{
		SDL_FreeSurface(tup.second);
	}
	
	res->clear();

	unordered_map<string, TTF_Font*>* resFont = &getInstance()->mResFonts;
	for (const pair<string, TTF_Font*>& tup : *resFont)
	{
		TTF_CloseFont(tup.second);
	}

	resFont->clear();
}

ResManager* ResManager::instancePtr = NULL;
