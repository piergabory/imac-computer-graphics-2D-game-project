#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "support/messages.h"
#include "support/window.h"

#include "gamedata.h"
#include "loadgame.h"
#include "updategame.h"
#include "collisions.h"

#define MAX_SPEED 1

#define ENEMY_DAMAGE -3
#define PROJECTILE_DAMAGE -1
#define WALL_DAMAGE -1
#define BONUS_HEALTH 5

static Game *gm = NULL;

Level getLevel();
Mob getPlayer();
MobList getMobList(char mob);

int initGame();

void updateGame();

void playerHit(MobList *ml, int damage);

void playerShoot();

void ennemyShoot(Mob e);

void changePlayerSpeedBy(float vx, float vy);

void playerHealth(int value);

int isHidden(Mob m);

#endif /* flapimac_h */
