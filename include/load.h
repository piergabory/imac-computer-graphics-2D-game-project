#ifndef load_h
#define load_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_LINE_LENGTH 512

#define MOB_TYPE_ENEMY 'e'
#define MOB_TYPE_BONUS 'b'

typedef struct world {
    int width, height;
    int *data;
} World;

typedef struct mobile {
    float ypos, xpos;
    unsigned char type;
    struct mobile *next;
} Mob, *MobList;




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

int loadWorld(char* path, World *w, MobList *enemy, MobList *bonus);

#endif /* load_h */
