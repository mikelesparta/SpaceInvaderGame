#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "Enemy.h"

#include <chrono>
#include <thread>

#define AUDIO_DISPARO "res/efecto_disparo.wav"

#define JUGADOR1 "res/jugador.png"
#define JUGADOR1_IZQ "res/jugador_izq.png"
#define JUGADOR2 "res/jugador2.png"
#define JUGADOR2_IZQ "res/jugador2_izq.png"
#define EXPLOSION_JUGADOR "res/explosion.png"

#define HEARTS 3

class Player : public Actor
{
public:
	Player(string filename1, string filename2, float x, float y, Game* game);

	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw() override; // Va a sobrescribir

	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;

	Animation* aShootingRight;
	Animation* aShootingLeft;

	Animation* aDying;
	Animation* animation; // Referencia a la animación mostrada

	Audio* audioShoot;

	string image;

	chrono::steady_clock::time_point lastCollisionTime;

	int shootCadence = 30;
	int shootTime = 0;
	int hearts;
	int orientation;
	int state;

	bool invincible;

	void impacted();
	void setInvincible(bool state);
	bool isInvincible();
};

