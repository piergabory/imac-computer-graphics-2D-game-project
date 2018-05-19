#ifndef gamedata_h
#define gamedata_h

#include <stdlib.h>
#include <stdio.h>

#include "structs/mob.struct.h"
#include "structs/level.struct.h"
#include "structs/game.struct.h"

#include "support/messages.h"

////// Memory allocation methods

/**
 * Alloc Level
 * -----------
 * Allocate memory for a level structure
 *
 * @param unsigned int width, width in 'blocks' of the level
 * @param unsigned int height, height in 'blocks' of the level
 *
 * @return Level* adress to the allocated memory
 */
Level* allocLevel(unsigned int width, unsigned int height);


/**
 * New Mob
 * -----------
 * Allocate memory for a mobile structure
 *
 * @param MobList *list reference to the list where the mob will be pushed into
 * @param unsigned char type, type of mob (defined in mob.struct)
 *
 * NOTE : Coordinates are a floating value between 0 and 1
 *        relative to the level dimentions.
 *        (ie: X=1 is on the end border of the world)
 *
 * @param float x, position on X axis in level
 * @param float y, position on Y axis in level
 *
 * @param float vx, speed
 * @param float vy, speed
 *
 * @return Level* adress to the allocated memory
 */
Mob* newMob(MobList *list, MobType type, float x, float y, float vx, float vy) ;


/**
 * Alloc Game
 * -----------
 * Allocate memory for a new game structure
 *
 * No params.
 *
 * @return Game* adress to the allocated memory
 */
Game* allocGame();



////// Memory de-allocation methods

/**
 * Mob Deallocation
 * ----------------
 * Free memory allocated for a removed mob.
 * Extract the mob out of it's list and link back the chain together
 *
 * @param Moblist *mob pointer to the chain link referencing the mob to freed
 */
void freeMob(MobList *mob);

/**
 * Games Deallocation
 * ----------------
 * Free memory of an active game
 * Free's the map, all mob lists and other variables
 *
 * @param Game *gm reference to game to free.
 */
void freeGame(Game *gm);

#endif /* gamedata_h */
