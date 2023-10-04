#pragma once

#include "Spaceship.h"
#include "Enemy.h"
#include "Actor.h"

Spaceship::Spaceship(string filename, float x, float y, int widthIcon, int heightIcon, Game* game)
	: Enemy(ICONO_ENEMIGO, x, y, 36, 40, game) {

	state = game->stateMoving;

	aDying = new Animation(ENEMIGO_MURIENDO, width, height,
		280, 40, 6, 8, false, game); //animaci�n finita

	aMoving = new Animation(ENEMIGO_MOVIMIENTO, width, height,
		108, 40, 6, 3, true, game);

	animation = aMoving;

	vx = 1;
}

void Spaceship::update() {
	// Actualizar la animaci�n
	bool endAnimation = animation->update();

	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
			cout << "Enemigo muerto" << endl;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}

	if (state == game->stateDying) {
		animation = aDying;
	}

	//Moverse mientras se muere
	if (state != game->stateDying) {
		vx = -1;
		x = x + vx;
	}
}
