#ifndef gamedata_h
#define gamedata_h

#define ENEMY 'e'
#define BONUS 'b'
#define OBSTACLE 'o'
#define PLAYER 'p'

#include <stdlib.h>
#include <stdio.h>

#include "messages.h"

// structure collecting world obstacles and game progress
typedef struct level {
    float progress;
    unsigned int width, height;
    unsigned int **map;
} Level;

// definition of any moving entity (player, enemy, projectiles etc..)
typedef struct mobile {
    float ay, ax;
    float vy, vx;
    float py, px;
    unsigned char type;
    struct mobile *next;
} Mob, *MobList;

// main structure
typedef struct game{
    Level *level;
    MobList enemies;
    MobList bonuses;
    MobList projectiles;
    Mob *player;
} Game;

// Memory allocation
Level* allocLevel(unsigned int width, unsigned int height);
Mob* allocMob(unsigned char type, float x, float y);
Game* allocGame();

// Memory de-allocation
void freeMob(MobList mob);
void freeGame(Game gm);

#endif /* gamedata_h */
