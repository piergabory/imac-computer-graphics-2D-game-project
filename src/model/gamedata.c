#include "model/gamedata.h"

// handy macro to handle malloc errors
#define HANDLE_MALLOC {printf(ERR_MALLOC); return NULL;}


/**
 * Alloc Level
 * -----------
 * Allocate memory for a level structure
 *
 * @param unsigned int width, width in 'blocks' of the level
 * @param unsigned int height, height in 'blocks' of the level
 *
 * @return Level* adress to the allocated memory
 */
Level* allocLevel(unsigned int width, unsigned int height) {
    // malloc and check
    Level *new = (Level*)malloc(sizeof(Level));
    if (new == NULL) HANDLE_MALLOC;
    
    // init values
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



/**
 * Alloc Mob
 * -----------
 * Allocate memory for a mobile structure
 *
 * @param MobList *list reference to the list where the mob will be pushed into
 * @param unsigned char type, type of mob (defined in header file)
 *
 * NOTE : Coordinates are a floating value between 0 and 1
 *        relative to the level dimentions.
 *        (ie: X=1 is on the end border of the world)
 * @param float x, position on X axis in level
 * @param float y, position on Y axis in level
 *
 * @param float vx, speed
 * @param float vy, speed
 *
 * @return Level* adress to the allocated memory
 */
Mob* newMob(MobList *list, char type, float x, float y, float vx, float vy) {
    // malloc and check
    Mob *new = (MobList) malloc(sizeof(Mob));
    if (new == NULL) HANDLE_MALLOC;
    
    // initisalize values
    new->px = x;
    new->py = y;
    
    new->vx = vx;
    new->vy = vy;
    
    new->health = 1;
    new->projectile_clock = 0;
    
    new->type = type;
    new->next = *list;
    
    return *list = new;
}



/**
 * Alloc Game
 * -----------
 * Allocate memory for a new game structure
 *
 * No params.
 *
 * @return Game* adress to the allocated memory
 */
Game* allocGame() {
    // malloc
    Game *new = (Game *) malloc(sizeof(Game));
    
    // allocate player
    new->player = (Mob*) malloc(sizeof(Mob));
    
    // initialize moblists
    new->enemies = NULL;
    new->bonuses = NULL;
    new->projectiles = NULL;
    new->enemy_projectiles = NULL;
    
    // check for malloc success
    if(new == NULL || new->player == NULL) HANDLE_MALLOC;
    
    return new;
}



/**
 * Mob Deallocation
 * ----------------
 * Free memory allocated for a removed mob.
 * Extract the mob out of it's list and link back the chain together
 *
 * @param Moblist *mob pointer to the chain link referencing the mob to freed
 */
void freeMob(MobList *mob) {
    // re-link the mob chain
    Mob *tmp = *mob;
    *mob = (*mob)->next;
    
    // free the extracted mob
    free(tmp);
    tmp = NULL;
}



/**
 * Games Deallocation
 * ----------------
 * Free memory of an active game
 * Free's the map, all mob lists and other variables
 *
 * @param Game gm to free.
 */
void freeGame(Game *gm) {
    // free player
    free(gm->player);

    
    // LEVEL
    
    // free map rows
    for (unsigned int i = 0; i < gm->level->height; i++) {
        free(gm->level->map[i]);
    }
    
    // free map
    free(gm->level->map);
    
    // free level
    free(gm->level);
    gm->level = NULL;
    
    
    // MOB LISTS
    
    // free mobs out of their list while the list has items.
    while (gm->enemies != NULL) {
        freeMob(&(gm->enemies));
    }
    
    while (gm->bonuses != NULL) {
        freeMob(&(gm->bonuses));
    }
    
    while (gm->projectiles != NULL) {
        freeMob(&(gm->projectiles));
    }
 
    while (gm->enemy_projectiles != NULL) {
        freeMob(&(gm->enemy_projectiles));
    }
    
    // free game structure
    free(gm);
}
