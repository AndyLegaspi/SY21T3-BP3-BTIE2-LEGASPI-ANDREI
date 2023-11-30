#include "SnakeBody.h"

void SnakeBody::start()
{
	texture = loadTexture("gfx/snakebody_3_30x30.png");
	x = 0;
	y = 0;
	speed = 6;
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void SnakeBody::update()
{

}

void SnakeBody::draw()
{
	blit(texture, x, y);
}

int SnakeBody::getPosX()
{
	return x;
}

int SnakeBody::getPosY()
{
	return y;
}

int SnakeBody::getWidth()
{
	return width;
}

int SnakeBody::getHeight()
{
	return height;
}

int SnakeBody::getSpeed()
{
	return speed;
}

void SnakeBody::setPosX(int xPos)
{
	this->x = xPos;
}

void SnakeBody::setPosY(int yPos)
{
	this->y = yPos;
}

void SnakeBody::setSpeed(int sSpeed)
{
	this->speed = sSpeed;
}

