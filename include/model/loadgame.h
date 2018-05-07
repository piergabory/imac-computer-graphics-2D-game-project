#ifndef loadgame_h
#define loadgame_h

#include <string.h>

#include "gamedata.h"

/**
 * LOAD WORLD (LEVEL) DATA
 * -----------------------
 * @param String path to the world's data file (.PPM format)
 * @param Game *gm reference to the game structure to initialize
 *
 * @return 0 if successful, other value if failed
 *
 * Load a .ppm (portable pixel map) image representing different element of the game world:
 * - red pixels represent obstacles
 * - green pixels represent enemies
 * - blue pixels represent bonuses
 * Will handle the file loading, parsing and edit of the world and mobile lists
 */
int loadWorld(char *path, Game *gm);



//// Temporary file used to remove comments out of the level files
//// CAUTION: '$ rm TEMP_FILE' is eventually executed
#define TEMP_FILE "tmp.ppm"

//// Lines begining with this character are ignored
#define PPM_COMMENT '#'

//// First characters of a valid PPM file
#define PPM_TYPE_1 "P6"
#define PPM_TYPE_2 "P3"

#endif /* loadgame_h */
