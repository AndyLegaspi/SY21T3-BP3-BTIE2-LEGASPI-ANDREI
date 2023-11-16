#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Background.h"
#include "PowerUps.h"
#include "Boss.h"

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
	Boss* boss;

	Background* background;
	Mix_Chunk* sound;

	float explosionTimer;
	float currExplTimer;

	float spawnTime;
	float currSpawnTimer;

	float currentPowerUpTimer;
	float powerUpTimer;

	float bossSpawnTimer;
	float bossTimerReset;

	std::vector<Enemy*> spawnedEnemies;
	std::vector<PowerUps*> spawnedPowerUps;

	void spawn();
	void deSpawn(Enemy* enemy);
	void checkSpawn();
	void spawnBoss();

	void collisionCheck();

	void memoryManage();

	void BackgroundDisplay();

	void deleteClaimedPowerUps(PowerUps* powerUp);
	void createPowerUps();
	void SpawnPowerUps();

	int points;
	int powerUpCount;

	int wave;
	int waveCount;
	int level;
	int tempWave;

	int bossCondition;
	int bossHP;
	int bossHPAdd;
};

