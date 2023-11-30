#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>
#include "util.h"
#include "Apple.h"

class Snake : public GameObject
{
public:
	void start();
	void update();
	void draw();  

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	int getDirX();
	int getDirY();

	bool getAlive();
	void doDeath();


private:
	SDL_Texture* texture;
	Mix_Chunk* sound;

	int directionHolder;
	int x;
	int y;
	int height;
	int width;
	int speed;
	int directionX;
	int directionY;
	bool isAlive;

	int up;
	int down;
	int left; 
	int right;
};

