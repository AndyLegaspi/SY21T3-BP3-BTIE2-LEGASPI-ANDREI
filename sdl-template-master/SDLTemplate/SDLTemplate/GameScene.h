#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	Player* player;
	Enemy* enemy;

	float spawnTime;
	float currSpawnTimer;
	std::vector<Enemy*> spawnedEnemies;

	void spawn();
	void deSpawn(Enemy* enemy);

	void checkSpawn();
	void collisionCheck();
	void memoryManage();

	int points;

	SDL_Texture* background;
	int bwidth;
	int bheight;
};

