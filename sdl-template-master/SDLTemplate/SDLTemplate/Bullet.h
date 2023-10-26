#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

enum class Side
{
	PLAYER_SIDE, 
	ENEMY_SIDE
};

class Bullet :
    public GameObject
{
public:
	Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side);
	virtual void start();
	virtual void update();
	virtual void draw();
	float getPositionX();
	float getPositionY();
	float getWidth();
	float getHeight();
	Side getSide();

private:
	SDL_Texture* texture;
	Side side;
	int x;
	int y;
	int width;
	int height;
	float speed;
	float directionX;
	float directionY;
};

