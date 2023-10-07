#include "Coin.h"

Coin::Coin(float x, float y, Game* game)
	: Actor(MONEDA, x, y, 40, 40, game) {

	state = game->stateMoving;

	aMoving = new Animation(MONEDA_MOVIMIENTO, width, height,
		131, 43, 6, 3, true, game);

	animation = aMoving;

	vx = 2;
}

void Coin::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	if (state != game->stateDying) {
		vx = -2;
		x = x + vx;
	}
}

void Coin::draw() {
	animation->draw(x, y);
}
