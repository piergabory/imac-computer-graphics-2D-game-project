#ifndef flapimac_h
#define flapimac_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "load.h"

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

#endif /* flapimac_h */
