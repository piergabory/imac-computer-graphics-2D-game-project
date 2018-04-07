#ifndef flapimac_h
#define flapimac_h

// Game logic

#define ENEMY 'e'
#define BONUS 'b'
#define OBSTACLE 'o'
#define PLAYER 'p'


typedef struct world {
    int width, height;
    int **data;
} World;

typedef struct mobile {
    float ypos, xpos;
    unsigned char type;
    struct mobile *next;
} Mob, *MobList;

World obstacleMap;
MobList enemies;
MobList bonuses;

#endif /* flapimac_h */
