#include "../include/game.h"

#define MAX_SPEED 1
#define DRAG 0.95

Game *initGame() {
    Game *gm;
    
    gm = (Game *) malloc(sizeof(Game));
    
    gm->level = (Level *) malloc(sizeof(Level));
    gm->enemies = (MobList*) malloc(sizeof(MobList));
    gm->bonuses = (MobList*) malloc(sizeof(MobList));
    gm->player = (Mob*) malloc(sizeof(Mob));
    
    // set player
    gm->player->px = 0;
    gm->player->py = 0;
    gm->player->vx = 0;
    gm->player->vy = 0;
    
    gm->player->type = PLAYER;
    gm->player->next = NULL;
    
    // set world
    loadWorld("image.ppm", gm);
    gm->level->progress = 0;
    
    return gm;
}

void updateGame(Game *gm) {
    // position
    gm->player->px += gm->player->vx;
    gm->player->py += gm->player->vy;
    
    // drag
    gm->player->vx *= DRAG;
    gm->player->vy *= DRAG;
    
    
    // bounce on borders
    if (gm->player->px > 1 || gm->player->px < 0) {
        gm->player->vx *= -1;
        gm->player->px = roundf(gm->player->px);
    }
    
    if (gm->player->py > 1 || gm->player->py < 0) {
        gm->player->vy *= -1;
        gm->player->py = roundf(gm->player->py);
    }
}

void changeXYSpeedBy(Mob *player, float vx, float vy) {
    if (fabs(player->vx + vx) < MAX_SPEED) player->vx += vx;
    if (fabs(player->vy + vy) < MAX_SPEED) player->vy += vy;
}


MobList allocMob(unsigned char type, float x, float y) {
    MobList new = (MobList)malloc(sizeof(Mob));
    if (new == NULL) {
        printf(ERR_MALLOC);
        return NULL;
    }
    
    new->px = x;
    new->py = y;
    new->type = type;
    new->next = NULL;
    
    return new;
}
