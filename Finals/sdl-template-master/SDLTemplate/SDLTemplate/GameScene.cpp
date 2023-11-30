#include "GameScene.h"
#include "text.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snake = new Snake();
	this->addGameObject(snake);

	initFonts();
	points = 0;
}

GameScene::~GameScene()
{
	delete snake;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	initFonts();
	bodySpawnTime = 10;

	doSpawnLogic();
}

void GameScene::draw()
{
	Scene::draw();
	drawText(0, 0, 255, 255, 255, TEXT_LEFT, "POINTS : %03d", points);

	if (snake->getAlive() == false) {
		drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "GAME OVER !!!");
		drawText(SCREEN_WIDTH / 2, 650, 255, 255, 255, TEXT_CENTER, "FINAL POINTS : %03d", points);
	}

	if (points == 0) {
		drawText(SCREEN_WIDTH / 2, 450, 255, 255, 255, TEXT_CENTER, "GAME WILL START WHEN YOU GRAB");
		drawText(SCREEN_WIDTH / 2, 500, 255, 255, 255, TEXT_CENTER, "FIRST APPLE");
	}
}

void GameScene::update()
{
	Scene::update();
	doCollisionLogic();

	bodyMove();

	if (snake->getPosX() > SCREEN_HEIGHT || snake->getPosY() > SCREEN_WIDTH || snake->getPosX() < 0 || snake->getPosY() < 0) {
		snake->doDeath();
	}
}

void GameScene::doSpawnLogic()
{
	spawn();
}

void GameScene::doCollisionLogic()
{
	// collision for Apple
	for (int i = 0; i < objects.size(); i++) {

		for (int i = 0; i < spawnedApples.size(); i++) {
			Apple* currentApple = spawnedApples[i];
			int collision = checkCollision(
				snake->getPosX(), snake->getPosY(), snake->getHeight(), snake->getWidth(),
				currentApple->getPosX(), currentApple->getPosY(), currentApple->getHeight(), currentApple->getWidth()
			);

			if (collision == 1) {
				despawnApple(currentApple);
				spawn();
				points++;
				addBody();
			}
		}

		// collision for Body
		for (int i = 0; i < spawnedBodies.size(); i++) {
			SnakeBody* currentSnakeBody = spawnedBodies[i];
			int collision = checkCollision(
				snake->getPosX(), snake->getPosY(), snake->getHeight(), snake->getWidth(),
				currentSnakeBody->getPosX(), currentSnakeBody->getPosY(), currentSnakeBody->getHeight(), currentSnakeBody->getWidth()
			);

			if (collision == 1) {
				snake->doDeath();
			}
		}

		// Apple wont spawn on snake body
		for (int i = 0; i < spawnedApples.size(); i++) {
			Apple* currentApple = spawnedApples[i];
			for (int i = 0; i < spawnedBodies.size(); i++) {
				SnakeBody* currentSnakeBody = spawnedBodies[i];
				int collision = checkCollision(
					currentApple->getPosX(), currentApple->getPosY(), currentApple->getHeight(), currentApple->getWidth(),
					currentSnakeBody->getPosX(), currentSnakeBody->getPosY(), currentSnakeBody->getHeight(), currentSnakeBody->getWidth()
				);
				if (collision == 1) {
					despawnApple(currentApple);
					spawn();
				}
			}
		}
	}
}

void GameScene::spawn()
{
	Apple* apple = new Apple();
	this->addGameObject(apple);

	apple->setPos(rand () % (SCREEN_WIDTH - 220), rand () % (SCREEN_HEIGHT -220));
	spawnedApples.push_back(apple);
}

void GameScene::despawnApple(Apple* apple)
{
	int idx = -1;
	for (int i = 0; i < spawnedApples.size(); i++) {
		if (apple == spawnedApples[i]) {
			idx = i;
			break;
		}
	}

	if (idx != 1) {
		spawnedApples.erase(spawnedApples.begin() + idx);
		delete apple;
	}
}

void GameScene::addBody()
{
	SnakeBody* snakeBody = new SnakeBody();
	this->addGameObject(snakeBody);
	spawnedBodies.push_back(snakeBody);
}

void GameScene::bodyMove()
{
	prevX = snake->getPosX();
	prevY = snake->getPosY();

	for (int i = 0; i < spawnedBodies.size(); i++) {
		SnakeBody* currentSnakeBody = spawnedBodies[i];
		prevX2 = currentSnakeBody->getPosX();
		prevY2 = currentSnakeBody->getPosY();
		currentSnakeBody->setPosX(prevX);
		currentSnakeBody->setPosY(prevY);
		prevX = prevX2;
		prevY = prevY2;
	}
}


