#include "Bomb.h"

Bomb::Bomb(float x, float y, Game* game)
	: Actor(BOMBA, x, y, 40, 40, game) {

	state = game->stateMoving;

	aDying = new Animation(BOOM, width, height,
		50, 50, 6, 1, false, game);

	aMoving = new Animation(BOMBA, width, height,
		35, 35, 6, 1, true, game);

	animation = aMoving;

	vx = 1;
}

void Bomb::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Explotando
		if (state == game->stateDying) {
			state = game->stateDead;
			cout << "BOOOOOOM" << endl;
		}
	}
	if (state == game->stateMoving) {
		animation = aMoving;
	}

	if (state == game->stateDying) {
		animation = aDying;
	}

	//Moverse mientars se muere
	if (state != game->stateDying) {
		vx = -5;
		x = x + vx;
	}
}

void Bomb::draw() {
	animation->draw(x, y);
}

void Bomb::explode() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}

	received = true;
}