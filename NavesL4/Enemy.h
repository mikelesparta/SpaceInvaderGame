#pragma once

#include "Actor.h"
#include "Animation.h" 

#define ENEMIGO_MURIENDO "res/enemigo_morir.png"
#define ENEMIGO_MOVIMIENTO "res/enemigo_movimiento.png"
#define ICONO_ASTEROIDE "res/asteroide.png"
#define ICONO_EXPLOSION "res/explosion_asteroide.png"

class Enemy : public Actor
{
public:
	//Enemy(float x, float y, Game* game);
	Enemy(string filename, float x, float y, int widthIcon, int heightIcon, Game* game);

	void draw() override; // Va a sobrescribir
	virtual void update();
	void impacted(); // Recibe impacto y pone animación de morir

	int state;

	Animation* aDying;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
};
