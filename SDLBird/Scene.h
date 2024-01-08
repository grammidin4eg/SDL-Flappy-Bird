#pragma once
#include <string>
#include <list>

#include "Object.h"

namespace GameObjects {
	class Scene
	{
	public:
		// создать сцену
		Scene();

		// очистить
		~Scene();

		// старт сцены
		void start();

		// обновить сцену
		void update();
		// отрисовать сцену
		void draw();

		// добавить объект
		void addObject(Object* obj);

		virtual void onInit(SDL_Renderer* renderer, SDL_Rect winSize);

		virtual void onStart(SDL_Renderer* renderer, SDL_Rect winSize);

	private:
		// список сцен
		std::list<Object*> mObjectList;
	};
};

