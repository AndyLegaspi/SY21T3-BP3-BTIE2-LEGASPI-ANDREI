#include "GameScene.h"

GameScene::GameScene()
{
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
	// Initialize any scene logic here
	background = loadTexture("gfx/background.png");
	bwidth = 0;
	bheight = 0;
	SDL_QueryTexture(background, NULL, NULL, &bwidth, &bheight);

	initFonts();

	currSpawnTimer = 300;
	spawnTime = 300;

	for (int i = 0; i < 3; i++) {
		spawn();
	}
}

void GameScene::draw()
{
	blitScale(background, 0, 0, &bwidth, &bheight, 3);
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
}

void GameScene::spawn()
{
	enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->setPlayerTarget(player);

	enemy->setPosition(1350, 400 + (rand() % 300));
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
						deSpawn(currentEnemy);
						points++;
						break;
					}
				}
			}
		}
	}
}

void GameScene::memoryManage()
{
	for (int i = 0; i < spawnedEnemies.size(); i++) {
		if (spawnedEnemies[i]->getPositionY() < -150 || spawnedEnemies[i]->getPositionX() < -150) {
			Enemy* enemies = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);
			delete enemies;
			break;
		}
	}
}
