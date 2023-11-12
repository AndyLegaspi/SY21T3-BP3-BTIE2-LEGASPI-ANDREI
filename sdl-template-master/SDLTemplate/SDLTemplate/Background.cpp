#include "Background.h"

void Background::start()
{
	texture = loadTexture("gfx/background.png");

	x = 0;
	y = 0;
	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Background::update()
{
}

void Background::draw()
{
	blitScale(texture, x, y, &width, &height, 3);
}
