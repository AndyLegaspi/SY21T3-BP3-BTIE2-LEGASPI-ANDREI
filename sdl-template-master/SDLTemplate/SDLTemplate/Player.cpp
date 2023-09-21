#include "Player.h"

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 3.5;
	boost = false;;
	noBoost = true;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	// SPEED BOOST 
	if (app.keyboard[SDL_SCANCODE_LSHIFT]) {
		boost = true;
		noBoost = false;
	}
	if (app.keyboard[SDL_SCANCODE_BACKSPACE]) {
		boost = false;
		noBoost = true;
	}

	// WASD MOVEMENT
	if (app.keyboard[SDL_SCANCODE_W]) {
		if (boost) {
			y -= speed + 5;
		}
		else {
			y -= speed;
		}
	}
	if (app.keyboard[SDL_SCANCODE_A]) {
		if (boost) {
			x -= speed + 5;
		}
		else {
			x -= speed;
		}
	}
	if (app.keyboard[SDL_SCANCODE_S]) {
		if (boost) {
			y += speed + 5;
		}
		else {
			y += speed;
		}
	}
	if (app.keyboard[SDL_SCANCODE_D]) {
		if (boost) {
			x += speed + 5;
		}
		else {
			x += speed;
		}
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
