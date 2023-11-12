#include "PowerUps.h"

PowerUps::PowerUps(float PositionX, float PositionY, float directionX, float directionY, float speed)
{
	this->x = PositionX;
	this->y = PositionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

void PowerUps::start()
{
	texture = loadTexture("gfx/points.png");

	width = 0;
	height = 0;
	powerUpLevel = 1;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUps::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void PowerUps::draw()
{
	blit(texture, x, y);
}

int PowerUps::getPositionX()
{
	return x;
}

int PowerUps::getPositionY()
{
	return y;
}

int PowerUps::getWidth()
{
	return width;
}

int PowerUps::getHeight()
{
	return height;
}

int PowerUps::getPowerUpLevel()
{
	return powerUpLevel;
}
