#ifndef collisions_h
#define collisions_h

#include <math.h>

#include "gamedata.h"
#include "game.h"

int isMobOnTerrain(Mob m, Level l);
int isMobOnMob(Mob m1, Mob m2);

// mob sizes relative to a sprite size
#define ENEMY_W 1
#define ENEMY_H 1

#define PLAYER_W 1
#define PLAYER_H 1

#define BONUS_W 1
#define BONUS_H 1

#define PROJECTILE_W 1
#define PROJECTILE_H 0.2

#endif /* collisions_h */
