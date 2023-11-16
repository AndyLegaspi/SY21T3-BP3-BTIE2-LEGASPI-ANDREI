#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Boss :
	public GameObject
{
public:
	Boss();
	~Boss();

	void start();
	void update();
	void draw();

	void setPlayerTarget(Player* player);

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	void isDead(bool isNotAlive);

private:
	SDL_Texture* texture;
	SDL_Texture* texture2;
	Mix_Chunk* sound;
	Mix_Chunk* sound2;
	Player* playerTarget;

	int x;
	int y;
	float directionX;
	float directionY;
	int width;
	int height;
	int speed;
	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;
	float timer;
	float reloadTime2;
	float currentReloadTime2;
	float reloadTime3;
	float currentReloadTime3;
	bool hasDied;

	std::vector<Bullet*> bullets;

	void MultipleBulletLogic();
	void IniTargetBullet();
	void BulletSpreadLogic();
	void MemoryManagement();
};
