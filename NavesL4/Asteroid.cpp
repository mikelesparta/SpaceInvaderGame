#pragma once

#include "Asteroid.h"
#include "Enemy.h"
#include "Actor.h"

Asteroid::Asteroid(string filename, float x, float y, int widthIcon, int heightIcon, Game* game)
	: Enemy(ICONO_ASTEROIDE, x, y, 50, 51, game) {

	state = game->stateMoving;

	aDying = new Animation(ICONO_EXPLOSION, width, height,
		53, 51, 6, 1, false, game); //animación finita

	aMoving = new Animation(ICONO_ASTEROIDE, width, height,
		50, 51, 6, 1, true, game);

	animation = aMoving;

	vy = 2;
}

void Asteroid::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
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
		vy = 2;
		y = y + vy;
	}
}

