#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Background.h"
#include "PowerUps.h"

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

	Background* background;

	float explosionTimer;
	float currExplTimer;

	float spawnTime;
	float currSpawnTimer;
	float currentPowerUpTimer;
	float powerUpTimer;

	std::vector<Enemy*> spawnedEnemies;
	std::vector<PowerUps*> spawnedPowerUps;

	void spawn();
	void deSpawn(Enemy* enemy);

	void checkSpawn();
	void collisionCheck();
	void memoryManage();
	void BackgroundDisplay();
	void deleteClaimedPowerUps(PowerUps* powerUp);
	void createPowerUps();
	void SpawnPowerUps();

	int points;
	int powerUpCount;
};

