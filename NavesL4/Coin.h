#pragma once

#include "Actor.h"
#include "Animation.h" 

#define MONEDA "res/moneda.png"
#define MONEDA_MOVIMIENTO "res/monedas_movimiento.png"

class Coin : public Actor
{
public:
	Coin(float x, float y, Game* game);

	void draw() override;
	void update();

	int state;
	bool received;

	Animation* aMoving;
	Animation* animation;
};

