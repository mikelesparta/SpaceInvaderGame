#pragma once

#include "Actor.h"
#include "Animation.h" 

#define BOMBA "res/bomba.png"
#define BOOM "res/boom.png"

class Bomb : public Actor
{
public:
	Bomb(float x, float y, Game* game);

	void draw() override;
	void update();
	void explode();

	int state;
	bool received;

	Animation* aDying;
	Animation* aMoving;
	Animation* animation;
};

