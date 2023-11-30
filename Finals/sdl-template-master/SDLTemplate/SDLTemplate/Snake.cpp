#include "Snake.h"
#include "Scene.h"

void Snake::start()
{
	texture = loadTexture("gfx/Snake_head_3_30x30.png");

	x = 100;
	y = 100;
	height = 0;
	width = 0;
	speed = 30;
	isAlive = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Snake::update()
{
	if (!isAlive) return;

	if (app.keyboard[SDL_SCANCODE_W])
	{
		if (down == 1) { return; }
		directionHolder = 1;
		//y -= speed;
		up = 1;
		down = 0;
		left = 0;
		right = 0;
		
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		if (up == 1) { return; }
		directionHolder = 2;
		//y += speed;
		up = 0;
		down = 1;
		left = 0;
		right = 0;
		
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		if (right == 1) { return; }
		directionHolder = 3;
		//x -= speed;
		up = 0;
		down = 0;
		left = 1;
		right = 0;
	
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		if (left == 1) { return; }
		directionHolder = 4;
		//x += speed;
		up = 0;
		down = 0;
		left = 0;
		right = 1;
		
	}

	if (directionHolder == 1 && down != 1) {
		y -= speed;
		SDL_Delay(100);
	}
	if (directionHolder == 2 && up != 1) {
		y += speed;
		SDL_Delay(100);
	}
	if (directionHolder == 3 && right != 1) {
		x -= speed;
		SDL_Delay(100);
	}
	if (directionHolder == 4 && left != 1) {
		x += speed;
		SDL_Delay(100);
	}
	
	
	
}

void Snake::draw()
{
	if (!isAlive) return;

	blit(texture, x, y);
}

int Snake::getPosX()
{
	return x;
}

int Snake::getPosY()
{
	return y;
}

int Snake::getWidth()
{
	return width;
}

int Snake::getHeight()
{
	return height;
}

int Snake::getDirX()
{
	return directionX;
}

int Snake::getDirY()
{
	return directionY;
}

bool Snake::getAlive()
{
	return isAlive;
}

void Snake::doDeath()
{
	isAlive = false;
}
