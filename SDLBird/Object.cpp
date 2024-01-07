#include "Object.h"

namespace GameObjects {
	Object::Object(SDL_Renderer* renderer)
	{
		mX = 0;
		mY = 0;
		mWidth = 0;
		mHeight = 0;

		mRenderer = renderer;
	}
	void Object::start()
	{
	}
	void Object::update()
	{
	}
	void Object::draw()
	{
	}
	void Object::free()
	{
	}
	int Object::getWidth()
	{
		return mWidth;
	}
	int Object::getHeight()
	{
		return mHeight;
	}
	void Object::setWidth(int width)
	{
		mWidth = width;
	}
	void Object::setHeight(int height)
	{
		mHeight = height;
	}
	void Object::setPos(int x, int y)
	{
		mX = x;
		mY = y;
	}
	int Object::getX()
	{
		return mX;
	}
	int Object::getY()
	{
		return mY;
	}
	SDL_Renderer* Object::getRenderer()
	{
		return mRenderer;
	}
}