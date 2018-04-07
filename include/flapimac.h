#ifndef flapimac_h
#define flapimac_h

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

Level level;
MobList enemies;
MobList bonuses;
Mob player;

int initGame();
void updateGame();

void changePlayerXYSpeedBy(float vx, float vy);

#endif /* flapimac_h */
