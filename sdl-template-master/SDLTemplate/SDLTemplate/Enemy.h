#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Enemy :
    public GameObject
{
public:
    Enemy();
    ~Enemy();

    void start();
    void update();
    void draw();
	void setPlayerTarget(Player* player);
	void setPosition(int xPos, int yPos);
	void setDirectionX(int dirX);

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

	void doDeath();
	

private:
	SDL_Texture* texture;
	SDL_Texture* texture2;
	Mix_Chunk* sound;
	Mix_Chunk* sound2;
	Player* playerTarget;

	int x;
	int y;
	int width;
	int height;
	float directionX;
	float directionY;
	float speed;

	float reloadTime;
	float currentReloadTime;
	float sReloadTime;
	
	float directionChangeTime;
	float currDirectionChangeTime;

	std::vector<Bullet*> bullets;

	bool isDead;
};

