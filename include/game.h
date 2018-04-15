#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>

#include "messages.h"
#include "gamedata.h"
#include "loadgame.h"
#include "updategame.h"
#include "collisions.h"

#define MAX_SPEED 1

static Game *gm = NULL;

Level getLevel();
Mob getPlayer();
MobList getMobList(char mob);

int initGame();

void updateGame();

void changePlayerSpeedBy(float vx, float vy);

void playerShoot();

#endif /* flapimac_h */
