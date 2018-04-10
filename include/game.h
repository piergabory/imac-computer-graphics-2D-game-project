#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "messages.h"

// Game logic

#define ENEMY 'e'
#define BONUS 'b'
#define OBSTACLE 'o'
#define PLAYER 'p'


typedef struct level {
    float progress;
    int width, height;
    int **map;
} Level;

typedef struct mobile {
    float ay, ax;
    float vy, vx;
    float py, px;
    unsigned char type;
    struct mobile *next;
} Mob, *MobList;

typedef struct game{
    Level *level;
    MobList *enemies;
    MobList *bonuses;
    Mob *player;
} Game;

Game *initGame();

void updateGame();

void changeXYSpeedBy(Mob *player, float vx, float vy);

MobList allocMob(unsigned char type, float x, float y);


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
