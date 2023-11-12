#include "GameScene.h"

GameScene::GameScene()
{
	BackgroundDisplay();

	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();

	initFonts();

	currSpawnTimer = 300;
	spawnTime = 300;

	currentPowerUpTimer = 300;
	powerUpTimer = 300;

	currExplTimer = 5;
	explosionTimer = 5;

	for (int i = 0; i < 3; i++) {
		spawn();
	}
}

void GameScene::draw()
{
	//blitScale(background, 0, 0, &bwidth, &bheight, 3);
	Scene::draw();
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false) {
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}
}

void GameScene::update()
{
	Scene::update();

	checkSpawn();
	collisionCheck();
	memoryManage();
	createPowerUps();
}

void GameScene::spawn()
{
	int randomNum = rand() % 2;
	Enemy* enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition((rand() % SCREEN_WIDTH + 1), -100);
	if (randomNum == 0) {
		enemy->setDirectionX(1);
	}
	else {
		enemy->setDirectionX(-1);
	}

	spawnedEnemies.push_back(enemy);
}

void GameScene::deSpawn(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++) {
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1) {
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}

}

void GameScene::checkSpawn()
{
	if (currSpawnTimer > 0)
		currSpawnTimer--;

	if (currSpawnTimer <= 0) {
		currSpawnTimer = spawnTime;

		for (int i = 0; i < 3; i++) {
			spawn();
		}
	}
}

void GameScene::collisionCheck()
{
	for (int i = 0; i < objects.size(); i++) {
		//cast to bullet
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);
		PowerUps* powerUps = dynamic_cast<PowerUps*> (objects[i]);
		//null check
		if (bullet != NULL) {
			//enemy bullet hits player
			if (bullet->getSide() == Side::ENEMY_SIDE) {
				int collision = checkCollision(
					player->getPosistionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1) {
					player->doDeath();
					break;
				}
			}

			//player bullet hits all enemies
			else if (bullet->getSide() == Side::PLAYER_SIDE) {
				for (int i = 0; i < spawnedEnemies.size(); i++) {
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1) {
						currentEnemy->doDeath();
						if (currExplTimer >= 0) {
							currExplTimer--;
						}
						if (currExplTimer <= 0) {
							deSpawn(currentEnemy);
							currExplTimer = explosionTimer;
						}
						points++;
						break;
					}
				}
			}
		}

		if (powerUps != NULL)
		{
			for (int i = 0; i < spawnedPowerUps.size(); i++)
			{
				PowerUps* currentPowerUp = spawnedPowerUps[i];

				int collision = checkCollision(
					player->getPosistionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					currentPowerUp->getPositionX(), currentPowerUp->getPositionY(), currentPowerUp->getWidth(), currentPowerUp->getHeight()
				);
				if (collision == 1)
				{
					powerUpCount++;
					player->setupPowerUp(powerUpCount);
					deleteClaimedPowerUps(currentPowerUp);
				}
			}
		}
	}
}

void GameScene::memoryManage()
{
	for (int i = 0; i < spawnedEnemies.size(); i++) {
		if (spawnedEnemies[i]->getPositionY() < -150 || spawnedEnemies[i]->getPositionX() < -150) {
			std::cout << "enemy deleted" << std::endl;
			Enemy* enemies = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemies;
			break;
		}
	}

	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		if (spawnedPowerUps[i]->getPositionY() > SCREEN_HEIGHT)
		{
			std::cout << "powerup deleted" << std::endl;
			PowerUps* powerUpsToDelete = spawnedPowerUps[i];
			spawnedPowerUps.erase(spawnedPowerUps.begin() + i);
			delete powerUpsToDelete;
			break;
		}
	}
}

void GameScene::BackgroundDisplay()
{
	background = new Background();
	this->addGameObject(background);
}

void GameScene::deleteClaimedPowerUps(PowerUps* powerUp)
{
	int index = -1;
	for (int i = 0; i < spawnedPowerUps.size(); i++)
	{
		if (powerUp == spawnedPowerUps[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		spawnedPowerUps.erase(spawnedPowerUps.begin() + index);
		delete powerUp;
	}
}

void GameScene::createPowerUps()
{
	if (currentPowerUpTimer > 0)
		currentPowerUpTimer--;

	if (currentPowerUpTimer == 0 && player->getIsAlive() == true)
	{
		SpawnPowerUps();
		currentPowerUpTimer = spawnTime;
	}
}

void GameScene::SpawnPowerUps()
{
	PowerUps* powerUp = new PowerUps(rand() % SCREEN_WIDTH + 1, -100, 0, 1, 2);
	this->addGameObject(powerUp);
	spawnedPowerUps.push_back(powerUp);
}
