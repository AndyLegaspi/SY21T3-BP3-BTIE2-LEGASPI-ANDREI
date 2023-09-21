#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"

class Player :
    public GameObject
{
public:
	virtual void start();
	virtual void update();
	virtual void draw();
private:
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
	float speed;
	bool boost;
	bool noBoost;
};

