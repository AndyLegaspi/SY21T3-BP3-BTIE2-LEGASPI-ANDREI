#include "Player.h"
#include "Scene.h"

// Deleting Bullets upon Player Death
Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");
	deathTexture = loadTexture("gfx/explosion.png");
	isAlive = true;
	isHit = false;

	x = SCREEN_WIDTH / 2 - 20;
	y = SCREEN_HEIGHT / 2 + 250;
	width = 0;
	height = 0;
	speed = 3.5;
	boost = false;;
	noBoost = true;
	reloadTime = 8;
	currentReloadTime = 0;
	sReloadTime = 16;
	sCurrentReloadTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound1 = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound->volume = 64;
	sound1->volume = 30;
}

void Player::update()
{
	// Memory Managing
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->getPositionX() > SCREEN_HEIGHT) {
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break;
		}
	}

	if (!isAlive) return;

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

	// SHOOTING
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0) {
		SoundManager::playSound(sound);
		
		DoShootingLogic();
		currentReloadTime = reloadTime;
	}

	if (sCurrentReloadTime > 0)
		sCurrentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_G] && sCurrentReloadTime == 0) {
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x - 12 + width / 2 + 35, y, 0, -1, 10, Side::PLAYER_SIDE);
		Bullet* bullet2 = new Bullet(x - 12 + width / 2 - 35, y, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		bullets.push_back(bullet2);
		getScene()->addGameObject(bullet);
		getScene()->addGameObject(bullet2);
		bullet->start();
		bullet2->start();

		sCurrentReloadTime = sReloadTime;
	}
}

void Player::draw()
{
	if (!isAlive) return;
	blitRotate(texture, x, y, 270);
}

int Player::getPosistionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::getIsAlive()
{
	return isAlive;
	SoundManager::playSound(sound1);
}

void Player::doDeath()
{
	isAlive = false;
	isHit = true;
}

void Player::setupPowerUp(int level)
{
	PowerUpLevel = level;
}

void Player::DoShootingLogic()
{
	if (PowerUpLevel == 0)
	{
		Bullet* bullet = new Bullet(x - 12 + width / 2, y, 0, -1, 10, Side::PLAYER_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}

	else if (PowerUpLevel >= 1)
	{
		float tempPowerup = 0;
		float tempPowerup2 = 0;

		for (int i = 0; i < PowerUpLevel; i++)
		{
			tempPowerup += .12;
			Bullet* bullet = new Bullet(x - 12 + width / 2, y, tempPowerup, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);

		}
		for (int i = -PowerUpLevel; i < 0; i++)
		{
			tempPowerup2 += .12;
			Bullet* bullet = new Bullet(x - 12 + width / 2, y, -tempPowerup2, -1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);

		}
	}
}
