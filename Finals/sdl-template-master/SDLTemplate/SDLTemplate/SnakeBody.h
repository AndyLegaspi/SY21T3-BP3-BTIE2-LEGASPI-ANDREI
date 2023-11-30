#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>
#include "util.h"

class SnakeBody : public GameObject
{
public:
	void start();
	void update();
	void draw();

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	int getSpeed();

	void setPosX(int xPos);
	void setPosY(int yPos);
	void setSpeed(int sSpeed);
	

private:
	SDL_Texture* texture;
	Mix_Chunk* sound;

	int x;
	int y;
	int height;
	int width;
	int speed;
};

