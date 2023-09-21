#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Bullet :
    public GameObject
{
public:
	Bullet(float positionX, float positionY, float directionX, float directionY, float speed);
	virtual void start();
	virtual void update();
	virtual void draw();
	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight();

private:
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
	float speed;
	float directionX;
	float directionY;
};

