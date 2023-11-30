#include "Apple.h"

void Apple::start()
{
	texture = loadTexture("gfx/appleSnake2.png");

	x = 0;
	y = 0;
	height = 0;
	width = 0;

	sound = SoundManager::loadSound("sound/coin_noise.ogg");
	
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Apple::update()
{

}

void Apple::draw()
{
	blit(texture, x, y);
}

int Apple::getPosX()
{
	return x;
}

int Apple::getPosY()
{
	return y;
}

int Apple::getWidth()
{
	return width;
}

int Apple::getHeight()
{
	return height;
}

void Apple::setPos(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
