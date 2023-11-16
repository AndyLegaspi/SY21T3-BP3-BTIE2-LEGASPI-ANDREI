#include "Boss.h"
#include "Scene.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::start()
{
	texture = loadTexture("gfx/enemy.png");
	texture2 = loadTexture("gfx/explosion.png");

	directionX = -1;
	directionY = 1;
	x = SCREEN_WIDTH / 2;
	y = -100;
	width = 0;
	height = 0;
	speed = 2;
	
	reloadTime = 10;
	currentReloadTime = 0;
	currentDirectionChangeTime = 0;

	reloadTime2 = 10;
	currentReloadTime2 = 0;

	reloadTime3 = 600;
	currentReloadTime3 = 0;

	timer = 180;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 16;
	sound2 = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound2->volume = 1;
}

void Boss::update()
{
	if (!hasDied) {

		srand(time(NULL));
		if(timer > 0){
			y += 1;
			timer--;
		}

		if(timer == 0){
			x += directionX * speed;
		}

		if(x < 0){
			directionX = -directionX;
		}
		else if(x >= SCREEN_WIDTH - 10){
			directionX = -directionX;
		}

		if(currentDirectionChangeTime > 0)
			currentDirectionChangeTime--;

		if(currentDirectionChangeTime == 0){
			directionX = -directionX;
			directionChangeTime = (rand() % 480) + 240;
			currentDirectionChangeTime = directionChangeTime;
		}

		if(currentReloadTime > 0){
			currentReloadTime--;
		}
		if(currentReloadTime2 > 0){
			currentReloadTime2--;
		}

		if(currentReloadTime3 > 0){
			currentReloadTime3--;
		}

		if(timer == 0){
			if(currentReloadTime == 0 && currentReloadTime3 > 300 && currentReloadTime3 < 520){

				SoundManager::playSound(sound);

				IniTargetBullet();

				currentReloadTime = reloadTime;
			}
		
			if(currentReloadTime3 == 0){
				SoundManager::playSound(sound);
				IniTargetBullet();
				currentReloadTime3 = reloadTime3;
			}

			if(currentReloadTime2 == 0 && currentReloadTime3 > 0 && currentReloadTime3 < 240){
				SoundManager::playSound(sound);
				IniTargetBullet();
				currentReloadTime2 = reloadTime2;
			}
		}
    }
}

void Boss::draw()
{
	if(!hasDied)
		blitRotate(texture, x, y, 180);
	else
		blitRotate(texture2, x, y, 180);
}

void Boss::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

int Boss::getPositionX()
{
	return x;
}

int Boss::getPositionY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}

void Boss::isDead(bool isNotAlive)
{
	hasDied = isNotAlive;
}

void Boss::MultipleBulletLogic()
{
	for(float i = 0; i < 3; i++){
		Bullet* bullet = new Bullet(x + width / 2, y + height - 50, i + .50, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}

	for(float i = -3; i < 0; i++){
		Bullet* bullet = new Bullet(x + width / 2, y + height - 50, i + .50, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}

void Boss::IniTargetBullet()
{
	float dx = -1;
	float dy = 0;

	calcSlope(playerTarget->getPosistionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

	Bullet* bullet = new Bullet(x + width / 2, y + height - 50, dx, dy, 4, Side::ENEMY_SIDE);
	bullets.push_back(bullet);
	getScene()->addGameObject(bullet);
}

void Boss::BulletSpreadLogic()
{
	float temp = -1;

	for (float i = 0; i < 9; i++){
		temp += .30f;
		Bullet* bullet = new Bullet(x + width / 2, y + height - 50, temp, 1, 10, Side::ENEMY_SIDE);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
	}
}

void Boss::MemoryManagement()
{
	for(int i = 0; i < bullets.size(); i++) {
		if(bullets[i]->getPositionY() > SCREEN_HEIGHT || bullets[i]->getPositionX() > SCREEN_WIDTH
			|| bullets[i]->getPositionX() < -100 || bullets[i]->getPositionY() < 0) {
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);

			delete bulletToErase;

			break;
		}
	}
}
