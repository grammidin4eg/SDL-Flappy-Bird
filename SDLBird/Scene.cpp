#include "Scene.h"
namespace GameObjects {
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		for (auto iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
		{
			(*iter)->free();
		}
	}

	void Scene::start()
	{
		for (auto iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
		{
			(*iter)->start();
		}
	}

	void Scene::update()
	{
		for (auto iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
		{
			(*iter)->update();
		}
	}

	void Scene::draw()
	{
		for (auto iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
		{
			(*iter)->draw();
		}
	}
	void Scene::addObject(Object* obj)
	{
		mObjectList.push_back(obj);
	}
	void Scene::onInit(SDL_Renderer* renderer, SDL_Rect winSize)
	{
	}
	void Scene::onStart(SDL_Renderer* renderer, SDL_Rect winSize)
	{
	}
}
