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
	unordered_map<string, SDL_Surface*>* res = &getInstance()->mRes;
	auto findedRes = res->find(name);
	if (findedRes != res->end())
	{
		return findedRes->second;
	}
	else
	{
		string path = "images/" + name;
		SDL_Surface* loadedImg = IMG_Load(path.c_str());
		exceptionIfNull(loadedImg, "Unable to load image");
		res->insert(make_pair(name, loadedImg));
		// printf("load: %s\n", name.c_str());
		return loadedImg;
	}
}

void ResManager::free()
{
	unordered_map<string, SDL_Surface*>* res = &getInstance()->mRes;
	for (const pair<string, SDL_Surface*>& tup : *res)
	{
		SDL_FreeSurface(tup.second);
	}
	
	res->clear();
}

ResManager* ResManager::instancePtr = NULL;
