#ifndef loadgame_h
#define loadgame_h

#include <string.h>

#include "gamedata.h"

/* LOAD WORLD DATA
 * ===============
 * @params: world-data file (.ppm) and references to an empty world, and moblists
 * @return: 0 if successful, other value if failed
 *
 * Load a .ppm (portable pixel map) image representing different element of the game world:
 * - red pixels represent obstacles
 * - green pixels represent enemies
 * - blue pixels represent bonuses
 * Will handle the file loading, parsing and edit of the world and mobile lists
 */

int loadWorld(char *path, Game *gm);

#define TEMP_FILE "tmp.ppm"
#define PPM_COMMENT '#'
#define PPM_TYPE_1 "P6"
#define PPM_TYPE_2 "P3"

#endif /* loadgame_h */
