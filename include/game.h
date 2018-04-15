#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>

#include "messages.h"
#include "gamedata.h"
#include "loadgame.h"
#include "updategame.h"
#include "collisions.h"


// Game logic

Game *initGame();

void updateGame();

void changePlayerSpeedBy(float vx, float vy);

void playerShoot();

#endif /* flapimac_h */
