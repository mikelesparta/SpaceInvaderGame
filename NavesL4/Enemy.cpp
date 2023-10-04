#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int widthIcon, int heightIcon, Game* game)
	: Actor(filename, x, y, 36, 40, game) {
}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

void Enemy::update() {
}