#pragma once
#include <SDL.h>
namespace GameObjects {
	class Object
	{
	public:
		Object(SDL_Renderer* renderer);
		virtual void update();
		virtual void draw();
		virtual void free();

		int getWidth();
		int getHeight();

		void setWidth(int width);
		void setHeight(int height);

		void setPos(int x, int y);

		int getX();
		int getY();

		SDL_Renderer* getRenderer();
	private:
		int mX;
		int mY;
		int mWidth;
		int mHeight;

		SDL_Renderer* mRenderer;
	};
}

