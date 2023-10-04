#include "Player.h"

Player::Player(string filename1, string filename2, float x, float y, Game* game)
	: Actor(filename1, x, y, 50, 57, game) {
	orientation = game->orientationRight; 
	state = game->stateMoving;
	invincible = false;
	hearts = HEARTS;
	image = filename1;

	audioShoot = new Audio(AUDIO_DISPARO, false);

	aShootingRight = new Animation(filename1,
		width, height, 50, 57, 6, 1, false, game);
	aShootingLeft = new Animation(filename2,
		width, height, 50, 57, 6, 1, false, game);

	aIdleRight = new Animation(filename1, width, height,
		50, 57, 6, 1, true, game);
	aIdleLeft = new Animation(filename2, width, height,
		50, 57, 6, 1, true, game);
	aRunningRight = new Animation(filename1, width, height,
		50, 57, 6, 1, true, game);
	aRunningLeft = new Animation(filename2, width, height,
		50, 57, 6, 1, true, game);

	aDying = new Animation(EXPLOSION_JUGADOR, width, height,
		50, 57, 6, 1, false, game); 

	animation = aIdleRight;
}

void Player::update() {
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {		
		// Estaba disparando
		if (state == game->stateShooting) {
			state = game->stateMoving;
		}
		else if (state == game->stateDying) {
			state = game->stateDead;
		}
	}

	// Estaba muriendo
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer orientación
	if (vx > 0) {
		orientation = game->orientationRight;
	}
	if (vx < 0) {
		orientation = game->orientationLeft;
	}

	// Selección de animación basada en estados
	if (state == game->stateShooting) {
		if (orientation == game->orientationRight) {
			animation = aShootingRight;
		}
		if (orientation == game->orientationLeft) {
			animation = aShootingLeft;
		}
	}
	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientation == game->orientationRight) {
				animation = aRunningRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aRunningLeft;
			}
		}
		if (vx == 0) {
			if (orientation == game->orientationRight) {
				animation = aIdleRight;
			}
			if (orientation == game->orientationLeft) {
				animation = aIdleLeft;
			}
		}
	}

	if (shootTime > 0) {
		shootTime--;
	}

	if (state != game->stateDying) {
		x = x + vx;
		y = y + vy;
	}
}

void Player::draw() {
	animation->draw(x, y);
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		//Creamos disparo, acción finita
		state = game->stateShooting;
		audioShoot->play();
		shootTime = shootCadence;

		//Para evitar el parpadeo tras disparar
		aShootingLeft->currentFrame = 0; //"Rebobinar" animación
		aShootingRight->currentFrame = 0; //"Rebobinar" animación
		Projectile* projectile = new Projectile(x, y, game);

		if (orientation == game->orientationLeft) {
			projectile->vx = projectile->vx * -1; // Invertir
		}
		
		return projectile;
	}
	else {
		return NULL;
	}
}

void Player::setInvincible(bool state) {
	invincible = state;
	lastCollisionTime = chrono::steady_clock::now();
}

bool Player:: isInvincible() {
	chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
	chrono::duration<double> elapsedTime = chrono::duration_cast<chrono::duration<double>>(currentTime - lastCollisionTime);
	return invincible && elapsedTime.count() < 3.0; // 3 seconds of invincibility
}

void Player::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

