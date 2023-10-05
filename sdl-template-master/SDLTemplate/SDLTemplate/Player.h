#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

class Player :
    public GameObject
{
public:
	~Player();
	virtual void start();
	virtual void update();
	virtual void draw();

	int getPosistionX();
	int getPositionY();
private:
	SDL_Texture* texture;
	Mix_Chunk* sound;

	int x;
	int y;
	int width;
	int height;
	float speed;
	bool boost;
	bool noBoost;
	float reloadTime;
	float currentReloadTime;
	float sReloadTime;
	float sCurrentReloadTime;

	std::vector<Bullet*> bullets;
};

