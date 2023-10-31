#pragma once

#include "Enemy.h"
#include "Animation.h" 

#define SPACHESHIP_DAMAGE 1

class Spaceship : public Enemy
{
public:
	Spaceship(string filename, float x, float y, int widthIcon, int heightIcon, Game* game);
	
	void update() override;
};

