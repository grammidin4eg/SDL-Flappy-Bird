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

		// обновить сцену
		void update();
		// отрисовать сцену
		void draw();

		// добавить объект
		void addObject(Object* obj);

	private:
		// список сцен
		std::list<Object*> mObjectList;
	};
};

