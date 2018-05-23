#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// prepared console messages (useful for a french version?)
#include "support/messages.h"

// initialize SDL
#include "support/window.h"


// data structures
#include "gamedata.h"

// level loader
#include "loadgame.h"

// physics for mobs
#include "updategame.h"

// physics between mobs (and the ground)
#include "collisions.h"

// Player default
#define PLAYER_STARTING_HEALTH 5
#define PLAYER_DEFAULT_SPEED 0.05

// Bonus effect intensity
#define SPEED_BUFF 1.5
#define WEAPON_BUFF 1.5

// Health Damages/Bonuses
typedef enum {
    ENEMY_DMG = -3,
    BONUS_DMG = 1,
    OBSTACLE_DMG = -1,
    ENEMY_PROJECTILE_DMG = -1
} Damage;

/**
 * Static global @ref to the active game structure
 */
static Game *gm = NULL;


//// GETTERS

/**
 * Level Getter
 * @return Level of the active game structure
 */
Level getLevel();

/**
 * Player mob Getter
 * @return Mob of the player in the active game structure
 */
Mob getPlayer();

/**
 * Mob List Getter
 * @param char Mobtype (defined in model/structs/mob.struct.h)
 * @return MobList of selected type, from the active game structure
 */
MobList getMobList(MobType type);




//// GAME METHODS


/**
 * Initialise Game
 * ---------------
 * Set the game structure to its sarting state
 * @return int success status boolean
 */
int initGame();


/**
 * Reset Game
 * ----------
 * 1. De-allocate active game structure off memory
 * 2. initialise a new one.
 */
void resetGame();


/**
 * Update Game
 * -----------
 * Controls the frame's computations for
 *    - Collisions
 *    - Physics
 *    - Player/Game Status/Progress/health
 *
 * Should be called in the SDL main loop
 */
void updateGame();



//// PLAYER METHODS

/**
 * Player Hit
 * ----------
 * Checks if the player has hit a mob in a given mob collection
 * if so applies damage (or health bonus) to the player and kills the mob
 *
 * @param MobList *ml, reference to the collections of mobs to check
 * @param int damage, value added to the player's health on collision
 *      -> Mob damage is defined above
 */
void playerHit(MobList *ml);


/**
 * Player Shoot
 * ------------
 * Spawns a player projectile on the player, with a fixed X velocity.
 */
void playerShoot();



/**
 * Player Health
 * -------------
 * Updates the player's health
 * Set game status to 'game over' if health reaches 0
 *
 * @param int health increment
 */
void playerHealth(Damage value);




/**
 * Ennemy Shoot
 * ------------
 * Spawns an ennemy projectile on a mob, with a fixed negative X velocity.
 * @param Mob e (ennemy), projectile source.
 */
void enemyShoot(Mob e);


/**
 * Is Mob Hidden
 * -------------
 * Tells if Mobs are on the viewport or not.
 * out of frame mobs should not be drawn or computed in collisions and physics updates.
 *
 * @param Mob m (mob) to check.
 * @return int 0 if in frame, 1 if out of bounds
 */
int isHidden(Mob m);

#endif /* flapimac_h */
