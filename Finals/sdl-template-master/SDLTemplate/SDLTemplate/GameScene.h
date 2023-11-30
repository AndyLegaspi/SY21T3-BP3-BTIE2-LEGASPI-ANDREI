#pragma once
#include "Scene.h"
#include "GameObject.h"
#include <vector>
#include "Snake.h"
#include "SnakeBody.h"
#include "Apple.h"
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
	Snake* snake;

	int points;

	std::vector<Apple*> spawnedApples;
	std::vector<SnakeBody*> spawnedBodies;
	void doSpawnLogic();
	void doCollisionLogic();
	void spawn();
	void despawnApple(Apple* apple);
	void addBody();
	void bodyMove();

	int prevX, prevY, prevX2, prevY2;

	int bodySpawnTime;
	int bodySpawnTimer;
};

