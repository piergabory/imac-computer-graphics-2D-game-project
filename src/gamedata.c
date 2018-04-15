#include "../include/gamedata.h"

#define HANDLE_MALLOC {printf(ERR_MALLOC); return NULL;}

Level* allocLevel(unsigned int width, unsigned int height) {
    Level *new = (Level*)malloc(sizeof(Level));
    if (new == NULL) HANDLE_MALLOC;
    
    new->width = width;
    new->height = height;
    new->progress = 0;
    
    // allocate map
    new->map = (unsigned int**) calloc(height, sizeof(unsigned int*));
    if (new->map == NULL) HANDLE_MALLOC;
    
    // allocate map rows
    for (unsigned int i = 0; i < height; i++) {
        new->map[i] = (unsigned int*) calloc(width, sizeof(unsigned int));
        if (new->map[i] == NULL) HANDLE_MALLOC;
    }
    
    return new;
}

Mob* allocMob(unsigned char type, float x, float y) {
    Mob *new = (MobList)malloc(sizeof(Mob));
    if (new == NULL) HANDLE_MALLOC;
    
    new->px = x;
    new->py = y;
    new->health = 1;
    new->type = type;
    new->next = NULL;
    
    return new;
}

Game* allocGame() {
    Game *new = (Game *) malloc(sizeof(Game));
    new->player = (Mob*) malloc(sizeof(Mob));
    new->enemies = NULL;
    new->bonuses = NULL;
    if(new == NULL || new->player == NULL) HANDLE_MALLOC;
    return new;
}

void freeMob(MobList *mob) {
    Mob *tmp = *mob;
    *mob = ((**mob).next);
    free(tmp);
    tmp = NULL;
}

void freeGame(Game gm) {
    // free player
    free(gm.player);
    
    // free mobs
    while (gm.enemies == NULL)
        freeMob(&(gm.enemies));
    
    while (gm.bonuses == NULL)
        freeMob(&(gm.bonuses));
    
    // free map
    for (unsigned int i = 0; i < gm.level->height; i++) {
        free(gm.level->map[i]);
    }
    free(gm.level->map);
    
    // free level
    free(gm.level);
    
    // free game
    free(&gm);
}
