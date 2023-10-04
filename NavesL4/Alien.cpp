#include "Alien.h"
#include "Enemy.h"

Alien::Alien(float x, float y, Game* game)
	 : Enemy(x, y, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game); //animación finita

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);

	animation = aMoving;

	vx = 1;
}

void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
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

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

