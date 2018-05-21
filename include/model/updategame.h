#ifndef updategame_h
#define updategame_h

#include <math.h>

#include "support/window.h"
#include "view/events.h"
#include "gamedata.h"

// drag effect on the player
#define DRAG 0.99

// fixed speed at witch the level moves towards the end
#define PROGRESS_RATE 0.0003

/**
 * Update Player Physics
 * ---------------------
 * updates position with the speed vector
 * updates speed vector with the DRAG value
 *
 * Makes the player bounce on the world limits (so he can't leave)
 *
 * @param Mob *p reference to the player mob structure
 */
void updatePlayer(Mob *p, Level *l);



/**
 * Update Ennemy Physics
 * ---------------------
 * IF the enemy is close to the player, move towards him
 * IF the enemy is far away, move predictably
 *
 * updates position from speed vector
 *
 * @param Mob *e reference to the enemy structure to update
 * @param Mob p copy of the player structure
 */
void updateEnemy(Mob *e, Mob p);



/**
 * Update (player/enemy) Projectile Physics
 * ----------------------------------------
 * updates projectile position from velocity vector
 *
 * @param Mob *p reference to the projectile structure
 */
void updateProjectile(Mob *p);

#endif /* updategame_h */
