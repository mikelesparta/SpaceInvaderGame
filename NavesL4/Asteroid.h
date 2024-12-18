#pragma once

#include "Enemy.h"
#include "Animation.h" 

#define ASTEROID_DAMAGE 2

class Asteroid : public Enemy
{
public:
	Asteroid(string filename, float x, float y, int widthIcon, int heightIcon, Game* game);
	void update() override;

};

