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

		// �������� �����
		void update();
		// ���������� �����
		void draw();

		// �������� ������
		void addObject(Object* obj);

	private:
		// ������ ����
		std::list<Object*> mObjectList;
	};
};

