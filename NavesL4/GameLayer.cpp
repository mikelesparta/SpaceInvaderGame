#include "GameLayer.h"

GameLayer::GameLayer(Game* game) :Layer(game) { 	//llama al constructor del padre : Layer(renderer)

	init();
}

void GameLayer::init() {
	audioBackground = new Audio(AUDIO_AMBIENTE, true);
	audioBackground->play();

	coins = 0;
	textCoins = new Text("coin", WIDTH * 0.83, HEIGHT * 0.05, game);
	textCoins->content = to_string(coins);

	points = 0;
	textPoints = new Text("points", WIDTH * 0.97, HEIGHT * 0.05, game);
	textPoints->content = to_string(points);

	players.clear(); // Vaciar por si reiniciamos el juego
	player = new Player(JUGADOR1, JUGADOR1_IZQ, 50, 50, game);
	player2 = new Player(JUGADOR2, JUGADOR2_IZQ, 50, 200, game);

	players.push_back(player);
	players.push_back(player2);

	background = new Background(FONDO, WIDTH * 0.5, HEIGHT * 0.5, -1, game);

	backgroundCoins = new Actor(COIN_ICON, WIDTH * 0.76, HEIGHT * 0.05, 24, 24, game);
	backgroungHearts.push_back(new Actor(HEART_ICON, WIDTH * 0.53, HEIGHT * 0.06, 24, 20, game));
	backgroungHearts.push_back(new Actor(HEART_ICON, WIDTH * 0.6, HEIGHT * 0.06, 24, 20, game));
	backgroungHearts.push_back(new Actor(HEART_ICON, WIDTH * 0.67, HEIGHT * 0.06, 24, 20, game));
	backgroungHeartsBlue.push_back(new Actor(BLUE_HEART_ICON, WIDTH * 0.32, HEIGHT * 0.06, 24, 20, game));
	backgroungHeartsBlue.push_back(new Actor(BLUE_HEART_ICON, WIDTH * 0.39, HEIGHT * 0.06, 24, 20, game));
	backgroungHeartsBlue.push_back(new Actor(BLUE_HEART_ICON, WIDTH * 0.46, HEIGHT * 0.06, 24, 20, game));
	backgroundPoints = new Actor(POINTS_ICON, WIDTH * 0.9, HEIGHT * 0.05, 24, 24, game);

	coinsList.clear();
	spaceships.clear();
	asteroids.clear();
	projectiles.clear();
	bombs.clear();

	spaceships.push_back(new Spaceship(ICONO_ENEMIGO, 300, 50, 36, 40, game));
}

void GameLayer::processControls() {
	// Obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}

	// Disparar Player1
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}

	// Disparar Player2
	if (controlShoot2) {
		Projectile* newProjectile = player2->shoot();
		if (newProjectile != NULL) {
			projectiles.push_back(newProjectile);
		}
	}

	// Eje X Player1
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y Player1
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

	// Eje X Player2
	if (controlMoveX2 > 0) {
		player2->moveX(1);
	}
	else if (controlMoveX2 < 0) {
		player2->moveX(-1);
	}
	else {
		player2->moveX(0);
	}

	// Eje Y Player2
	if (controlMoveY2 > 0) {
		player2->moveY(1);
	}
	else if (controlMoveY2 < 0) {
		player2->moveY(-1);
	}
	else {
		player2->moveY(0);
	}
}

void GameLayer::update() {
	list<Player*> deletePlayers;
	list<Spaceship*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Asteroid*> deleteAsteroids;
	list<Coin*> deleteCoins;
	list<Bomb*> deleteBombs;

	background->update();

	for (auto const& onePlayer : players) {
		onePlayer->update();
	}

	for (auto const& enemy : spaceships) {
		enemy->update();
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& coin : coinsList) {
		coin->update();
	}

	for (auto const& asteroid : asteroids) {
		asteroid->update();
	}

	for (auto const& bomb : bombs) {
		bomb->update();
	}

	// Generar enemigos
	newEnemyTime--;
	if (newEnemyTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		spaceships.push_back(new  Spaceship(ICONO_ENEMIGO, rX, rY, 36, 40, game));
		newEnemyTime = 110;
	}

	//EXTENSION: Generar monedas
	newCoinTime--;
	if (newCoinTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		coinsList.push_back(new Coin(rX, rY, game));
		newCoinTime = 250;
	}

	//EXTENSION: Generar asteroides
	newAsteroidTime--;
	if (newAsteroidTime <= 0) {
		int rX = (rand() % (300 - 100)) + 1 + 100;
		asteroids.push_back(new Asteroid(ICONO_ASTEROIDE, rX, 0, 50, 51, game));
		newAsteroidTime = 300;
	}

	//EXTENSION: Generar bombas
	newBombTime--;
	if (newBombTime <= 0) {
		int rX = (rand() % (600 - 500)) + 1 + 500;
		int rY = (rand() % (300 - 60)) + 1 + 60;
		bombs.push_back(new Bomb(rX, rY, game));
		newBombTime = 400;
	}

	// Colisiones: Player - Spaceship
	for (auto const& spaceship : spaceships) {
		for (auto const& onePlayer : players) {
			if (onePlayer->isOverlap(spaceship)) {
				if (!onePlayer->invincible) {
					cout << "La nave ha colisionado con un enemigo" << endl;

					spaceship->impacted(); //Empieza a morir
					onePlayer->hearts -= SPACHESHIP_DAMAGE;
					onePlayer->setInvincible(true);

					if (onePlayer->image == JUGADOR1) {
						backgroungHearts.pop_front();
					}
					else {
						backgroungHeartsBlue.pop_front();
					}

					if (onePlayer->hearts <= 0) {
						onePlayer->impacted(); //Empieza a morir
					}

					checkPlayersAlive(); //Comprobar GAME OVER
				}
				return; // Cortar el for
			}
		}
	}

	//EXTENSION: Colisones: Player - Coin
	for (auto const& coin : coinsList) {
		for (auto const& onePlayer : players) {
			if (onePlayer->isOverlap(coin) && coin->received == false) {
				cout << "Obtenido una moneda" << endl;

				bool pInList = std::find(deleteCoins.begin(),
					deleteCoins.end(),
					coin) != deleteCoins.end();

				if (!pInList) {
					deleteCoins.push_back(coin);
				}

				coin->state = game->stateDead;
				coin->received = true;				
				coins++; //Actualizamos el contador de monedas
				textCoins->content = to_string(coins);
			}
		}
	}

	// Colisiones: Enemy - Projectile
	for (auto const& projectile : projectiles) {
		if (projectile->isInRender() == false) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : spaceships) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
								
				enemy->impacted(); //Empieza a morir
				cout << "Impactado con proyectil" << endl;
				points++;
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& enemy : spaceships) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	// Colisiones: Asteroid - Projectile
	for (auto const& asteroid : asteroids) {
		for (auto const& projectile : projectiles) {
			if (asteroid->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				asteroid->impacted(); //Empieza a morirse
				cout << "Asteroide destruido" << endl;
				points++;
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& enemy : spaceships) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	// Colisiones: Player - Asteroid
	for (auto const& asteroid : asteroids) {
		for (auto const& onePlayer : players) {
			if (onePlayer->isOverlap(asteroid)) {
				if (!onePlayer->invincible) {
					cout << "La nave ha colisionado con un asteroide" << endl;
					
					//Quitar 1 corazón	
					if (onePlayer->hearts == HEARTS - 2) { 					
						onePlayer->hearts -= ASTEROID_DAMAGE;

						if (onePlayer->image == JUGADOR1) {
							backgroungHearts.pop_front();

						}
						else {
							backgroungHeartsBlue.pop_front();
						}
					}

					//Quitar 2 corazones	
					else if (onePlayer->hearts >= HEARTS - 1) {
						onePlayer->hearts -= ASTEROID_DAMAGE;

						if (onePlayer->image == JUGADOR1) {
							backgroungHearts.pop_front();
							backgroungHearts.pop_front();
						}
						else {
							backgroungHeartsBlue.pop_front();
							backgroungHeartsBlue.pop_front();
						}
					}

					asteroid->impacted(); //empieza a morir
					onePlayer->setInvincible(true);

					//Si no le quedan vidas al jugador, empieza a morir
					if (onePlayer->hearts <= 0) {
						onePlayer->impacted();
					}

					checkPlayersAlive();
				}
				return; // Cortar el for
			}
		}
	}

	for (auto const& asteroid : asteroids) {
		if (asteroid->state == game->stateDead) {
			bool eInList = std::find(deleteAsteroids.begin(),
				deleteAsteroids.end(),
				asteroid) != deleteAsteroids.end();

			if (!eInList) {
				deleteAsteroids.push_back(asteroid);
			}
		}
	}

	for (auto const& onePlayer : players) {
		if (onePlayer->state == game->stateDead) {
			bool eInList = std::find(deletePlayers.begin(),
				deletePlayers.end(),
				onePlayer) != deletePlayers.end();

			if (!eInList) {
				deletePlayers.push_back(onePlayer);
			}
		}
	}

	//EXTENSION: Colisones: Player - Bomb
	for (auto const& bomb : bombs) {
		for (auto const& onePlayer : players) {
			if (onePlayer->isOverlap(bomb) && bomb->received == false) {
				cout << "Power Up BOOM" << endl;

				//Bomba y enemigos empiezan a morir
				bomb->explode();

				for (auto const& spaceship : spaceships) {
					spaceship->impacted();
				}

				for (auto const& asteroid : asteroids) {
					asteroid->impacted();
				}
			}
		}
	}

	for (auto const& bomb : bombs) {
		if (bomb->state == game->stateDead) {
			bool eInList = std::find(deleteBombs.begin(),
				deleteBombs.end(),
				bomb) != deleteBombs.end();

			if (!eInList) {
				deleteBombs.push_back(bomb);
			}
		}
	}

	for (auto const& onePlayer : deletePlayers) {
		players.remove(onePlayer);
	}

	deletePlayers.clear();

	for (auto const& onePlayer : players) {
		if (onePlayer->invincible == true) {
			onePlayer->setInvincible(false);
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		spaceships.remove(delEnemy);
	}

	deleteEnemies.clear();

	for (auto const& asteroid : deleteAsteroids) {
		asteroids.remove(asteroid);
	}

	deleteAsteroids.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile;
	}

	deleteProjectiles.clear();

	for (auto const& coin : deleteCoins) {
		coinsList.remove(coin);
	}

	deleteCoins.clear();

	for (auto const& bomb : deleteBombs) {
		bombs.remove(bomb);
	}

	deleteBombs.clear();
}

void GameLayer::draw() {
	background->draw();
	
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	for (auto const& onePlayer : players) {
		onePlayer->draw();
	}

	for (auto const& enemy : spaceships) {
		enemy->draw();
	}

	for (auto const& coin : coinsList) {
		coin->draw();
	}

	for (auto const& asteroid : asteroids) {
		asteroid->draw();
	}

	for (auto const& bomb : bombs) {
		bomb->draw();
	}

	backgroundPoints->draw();
	textPoints->draw();

	backgroundCoins->draw();
	textCoins->draw();

	for (auto const& heart : backgroungHearts) {
		heart->draw();
	}

	for (auto const& blueHeart : backgroungHeartsBlue) {
		blueHeart->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;

		// Tecla pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;

		//Player1
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;

		//Player2
		case SDLK_RIGHT: // derecha
			controlMoveX2 = 1;
			break;
		case SDLK_LEFT: // izquierda
			controlMoveX2 = -1;
			break;
		case SDLK_UP: // arriba
			controlMoveY2 = -1;
			break;
		case SDLK_DOWN: // abajo
			controlMoveY2 = 1;
			break;
		case SDLK_RSHIFT: // dispara
			controlShoot2 = true;
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;

		// Tecla levantada
		switch (code) {
			//Player1
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;

		//Player2
		case SDLK_RIGHT: // derecha
			if (controlMoveX2 == 1) {
				controlMoveX2 = 0;
			}
			break;
		case SDLK_LEFT: // izquierda
			if (controlMoveX2 == -1) {
				controlMoveX2 = 0;
			}
			break;
		case SDLK_UP: // arriba
			if (controlMoveY2 == -1) {
				controlMoveY2 = 0;
			}
			break;
		case SDLK_DOWN: // abajo
			if (controlMoveY2 == 1) {
				controlMoveY2 = 0;
			}
			break;
		case SDLK_RSHIFT: // dispara
			controlShoot2 = false;
			break;
		}
	}
}

void GameLayer::checkPlayersAlive() {
	if (player->hearts <= 0 && player2->hearts <= 0) {
		cout << "GAME OVER" << endl;
		cout << endl;
		cout << "REINICIANDO JUEGO" << endl;
		init();
		return;
	}
}