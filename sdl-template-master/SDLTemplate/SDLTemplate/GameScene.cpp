#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	currSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++) {
		spawn();
	}
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
	if (currSpawnTimer > 0)
		currSpawnTimer--;

	if (currSpawnTimer <= 0) {
		currSpawnTimer = spawnTime;

		for (int i = 0; i < 3; i++) {
			spawn();
		}
	}

	//Memory Management
	for (int i = 0; i < spawnedEnemies.size(); i++) {
		if (spawnedEnemies[i]->getPositionY() < -150 || spawnedEnemies[i]->getPositionX() < -150) {
			Enemy* enemies = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemies;
			break;
		}
	}
}

void GameScene::spawn()
{
	enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1350, 400 + (rand() % 300));
	spawnedEnemies.push_back(enemy);
}
