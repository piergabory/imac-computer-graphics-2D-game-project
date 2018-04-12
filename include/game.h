#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "gamedata.h"
#include "messages.h"

// Game logic



Game *initGame();

void updateGame();

void changeXYSpeedBy(Mob *player, float vx, float vy);



/* LOAD WORLD DATA
 * ===============
 * @params: world-data file (.ppm) and references to an empty world and moblists
 * @return: 0 if successful, other value if failed
 *
 * Load a .ppm (portable pixel map) image representing different element of the game world:
 * - red pixels represent obstacles
 * - green pixels represent enemies
 * - blue pixels represent bonuses
 * Will handle the file loading, parsing and edit of the world and mobile lists
 */

int loadWorld(char *path, Game *gm);

#endif /* flapimac_h */
