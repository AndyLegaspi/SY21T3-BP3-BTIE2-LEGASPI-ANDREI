#include "GameScene.h"

GameScene::GameScene()
{
	BackgroundDisplay();

	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
	wave = 0;
	waveCount = 5;
	level = 1;

	bossCondition = 0;
	bossHP = 50;
	bossHPAdd = bossHP;
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

	bossSpawnTimer = 300;
	bossTimerReset = bossSpawnTimer;

	for (int i = 0; i < 3; i++) {
		spawn();
	}

	sound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound->volume = 1;
}

void GameScene::draw()
{
	//blitScale(background, 0, 0, &bwidth, &bheight, 3);
	Scene::draw();
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false) {
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20, 255, 255, 255, TEXT_CENTER, "GAME OVER");
	}

	if (bossCondition == 1){
		drawText(SCREEN_WIDTH / 2, 200, 255, 255, 255, TEXT_CENTER, "BOSS HEALTH: %03d", bossHP);
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
	if (wave < waveCount && player->getIsAlive() == true) {
		if (currSpawnTimer > 0)
			currSpawnTimer--;

		if (currSpawnTimer <= 0) {
			currSpawnTimer = spawnTime;

			for (int i = 0; i < 3; i++) {
				spawn();
			}
			wave += 1;
		}
		tempWave = wave;
	}
	else if (tempWave == waveCount){

		if (bossSpawnTimer > 0)
			bossSpawnTimer--;

		if (bossSpawnTimer == 0){
			//player->setupPowerUp(0);
			powerUpCount = 0;
			//spawnBoss();
			tempWave = 0;
			bossCondition = 1;
		}
	}
}

void GameScene::spawnBoss()
{
	Boss* boss = new Boss();
	this->addGameObject(boss);
	boss->setPlayerTarget(player);
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

				if (bossCondition == 1)
				{
					int collision = checkCollision(
						boss->getPositionX(), boss->getPositionY(), boss->getWidth(), boss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);
					if (collision == 1)
					{
						bossHP -= 1;
						SoundManager::playSound(sound);
						sound->volume = 1;
						if (bossHP == 0)
						{
							SoundManager::playSound(sound);
							sound->volume = 1;
							delete boss;
							bossSpawnTimer = bossTimerReset;
							bossCondition = 0;
							wave = 0;
							level += 1;
							bossHPAdd *= 2;
							bossHP = bossHPAdd;
							points += 1000;
							waveCount += 1;
						}
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
