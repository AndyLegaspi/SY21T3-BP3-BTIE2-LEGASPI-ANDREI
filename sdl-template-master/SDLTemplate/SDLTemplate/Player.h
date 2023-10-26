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
	int getWidth();
	int getHeight();
	bool getIsAlive();
	void doDeath();
private:
	SDL_Texture* texture;
	SDL_Texture* deathTexture;
	Mix_Chunk* sound;
	Mix_Chunk* sound1;

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
	bool isAlive;
	bool isHit;

	std::vector<Bullet*> bullets;
};

