#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>
#include "util.h"

class Apple :  public GameObject
{
public:
	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

	void setPos(int xPos, int yPos);

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;

	int x;
	int y;
	int height;
	int width;

	int spawnTime;
	int currentSpawnTime;
};

