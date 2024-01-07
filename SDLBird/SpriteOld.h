#pragma once

#include <stdio.h>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>


#include "utils.h";


class SpriteOld
{
public:
	// Создать пустой спрайт
	SpriteOld(SDL_Renderer* renderer);

	// Создать спрайт из файла
	SpriteOld(SDL_Renderer* renderer, std::string name);

	~SpriteOld();
	
	void draw();
	void drawToPos(int x, int y);

	void setClip(SDL_Rect* clip);

	int getWidth();
	int getHeight();

	void setWidth(int width);
	void setHeight(int height);

	void setPos(int x, int y);

	int getX();
	int getY();

	void setAngle(double angle);
	void setFlip(SDL_RendererFlip flip);

	void setCheckCollision(bool check);
	bool isCheckCollision();
	bool checkCollision(SpriteOld* another);

	void removeImage();


protected:
	int mX;
	int mY;
	void init();
	void loadSurface(SDL_Surface* loadedSurface);
private:
	int mWidth;
	int mHeight;

	// область, которую рисуем из спрайта
	SDL_Rect* mClip;

	// угол поворота
	double mAngle;
	SDL_RendererFlip mFlip;

	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	bool mCheckCollision;

};

