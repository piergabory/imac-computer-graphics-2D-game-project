#ifndef collisions_h
#define collisions_h

#include <math.h>

#include "gamedata.h"
#include "game.h"

/**
 * IS Mob On Terrain
 * -----------------
 * Get the terrain type if the mob is hitting the ground.
 * 0 if still flying fine.
 *
 * @param Mob m, the mob to check
 * @param Level l, the terrain mob might be crashing into
 *
 * @return int terrain type, 0 if no collisions
 */
int isMobOnTerrain(Mob m, Level l);


/**
 * IS Mob On Mob
 * -------------
 * Check if two mobs are colliding each other
 *
 * @param Mob m1, first mob
 * @param Mob m2, second mob
 *
 * @return Int boolean (0 or 1) if m1's hitbox overlaps m2's
 */
int isMobOnMob(Mob m1, Mob m2);


/**
 * IS Mob On Mob List
 * ------------------
 * Check if a mob is hitting at least one other mob out of a collection of mobs.
 *
 * @param Mob m, mob to check
 * @param MobList *ml, reference to the collection of mobs
 *
 * @return MobList *mob, reference to the MobList referencing to the hitted mob
 * @return NULL if no collisions
 */
MobList *isMobOnMoblist(Mob m, MobList *ml);


//// mob sizes relative to a sprite size

// enemy
#define ENEMY_W 1
#define ENEMY_H 1

// player
#define PLAYER_W 1
#define PLAYER_H 1

// bonus
#define BONUS_W 0.6
#define BONUS_H 0.6

// projectile
#define PROJECTILE_W 0.4
#define PROJECTILE_H 0.2

// enemy projectile
#define ENEMY_PROJECTILE_W 0.4
#define ENEMY_PROJECTILE_H 0.2

#endif /* collisions_h */
