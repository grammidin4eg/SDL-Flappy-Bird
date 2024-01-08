#pragma once
#include <string>
#include <list>

#include "Object.h"

namespace GameObjects {
	class Scene
	{
	public:
		// ������� �����
		Scene();

		// ��������
		~Scene();

		// ����� �����
		void start();

		// �������� �����
		void update();
		// ���������� �����
		void draw();

		// �������� ������
		void addObject(Object* obj);

		virtual void onInit(SDL_Renderer* renderer, SDL_Rect winSize);

		virtual void onStart(SDL_Renderer* renderer, SDL_Rect winSize);

	private:
		// ������ ����
		std::list<Object*> mObjectList;
	};
};

