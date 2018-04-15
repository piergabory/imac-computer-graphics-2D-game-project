#include "../include/game.h"

static Game *gm = NULL;

Game *initGame() {
    gm = allocGame();
    
    // set player
    gm->player->px = 0;
    gm->player->py = 0;
    gm->player->vx = 0;
    gm->player->vy = 0;
    
    gm->player->type = PLAYER;
    gm->player->next = NULL;
    
    // set level, ennemies and bonuses
    if(loadWorld("map.ppm", gm) != 0){
        printf(ERR_LOADWORLD);
        return NULL;
    }
    
    // set projectiles
    gm->projectiles = NULL;
    
    return gm;
}

void updateGame() {
    gm->level->progress += 0.1;
    
    updatePlayer(gm->player);
    
    Mob *current = gm->enemies;
    while (current != NULL) {
        updateEnnemy(current);
        current = current->next;
    }
    
    current = gm->projectiles;
    while (current != NULL) {
        updateProjectile(current);
        current = current->next;
    }
}

void changePlayerSpeedBy(float vx, float vy) {
    if (fabs(gm->player->vx + vx) < MAX_SPEED) gm->player->vx += vx;
    if (fabs(gm->player->vy + vy) < MAX_SPEED) gm->player->vy += vy;
}

void playerShoot() {
    Mob *tmp = gm->projectiles;
    gm->projectiles = allocMob(PROJECTILE, gm->player->px, gm->player->py);
    gm->projectiles->next = tmp;
    gm->projectiles->vx = 0.001;
}



