#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	texture = loadTexture("gfx/enemy.png");

	directionX = -1;
	direrctionY = 1;
	width = 0;
	height = 0;
	speed = 1.5;

	reloadTime = 60;
	currentReloadTime = 0;

	directionChangeTime = (rand() % 300) + 180;
	currDirectionChangeTime = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 16;
}

void Enemy::update()
{
	//Direction
	x += directionX * speed;
	y += direrctionY * speed;

	if (currDirectionChangeTime > 0)
		currDirectionChangeTime--;

	if (currDirectionChangeTime == 0) {
		direrctionY = -direrctionY;
		currDirectionChangeTime = directionChangeTime;
	}

	//Auto Firing
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0) {
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPosistionX(), playerTarget->getPositionY(), x, y, &dx,&dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width - 5, y + height / 2 - 4, dx, dy, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}

	// Memory Managing
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->getPositionX() < 0 || bullets[i]->getPositionY() < 0 || bullets[i]->getPositionY() > 900) {
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Enemy::getPositionX()
{
	return x;
}

int Enemy::getPositionY()
{
	return y;
}

int Enemy::getWidth()
{
	return width;
}

int Enemy::getHeight()
{
	return height;
}
