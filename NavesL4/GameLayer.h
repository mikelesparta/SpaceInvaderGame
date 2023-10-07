#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Coin.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h" 
#include "Spaceship.h"
#include "Asteroid.h"
#include "Bomb.h"

#include <list>
#include <chrono>
#include <thread>

#define AUDIO_AMBIENTE "res/musica_ambiente.mp3"
#define FONDO "res/fondo.png"
#define HEART_ICON "res/corazon.png"
#define BLUE_HEART_ICON "res/corazon_azul.png"
#define POINTS_ICON "res/icono_puntos.png"
#define COIN_ICON "res/moneda_icon.png"

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);

	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void checkPlayersAlive();

	Audio* audioBackground;
	Text* textPoints;
	Text* textCoins;

	int points;
	int coins;
	int newCoinTime = 0;
	int newEnemyTime = 0;
	int newAsteroidTime = 0;
	int newBombTime = 0;

	Player* player;
	Player* player2;

	list<Player*> players;
	list<Spaceship*> spaceships;
	list<Asteroid*> asteroids;
	list<Projectile*> projectiles;
	list<Coin*> coinsList;
	list<Bomb*> bombs;
	list<Actor*> backgroungHearts;
	list<Actor*> backgroungHeartsBlue;


	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundCoins;
	
	int controlMoveX = 0;
	int controlMoveY = 0;
	int controlMoveX2 = 0;
	int controlMoveY2 = 0;

	bool controlShoot = false;
	bool controlShoot2 = false;
};

