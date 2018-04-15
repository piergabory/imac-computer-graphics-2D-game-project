#include "../include/game.h"

Level getLevel() {return *(gm->level); }

Mob getPlayer() { return *(gm->player); }

MobList getMobList(char mob) {
    switch (mob) {
        case 'e': return gm->enemies;
        case 'b': return gm->bonuses;
        case 'j': return gm->projectiles;
        case 'p': return gm->player;
        default: return NULL;
    }
}

int initGame() {
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
        return 0;
    }
    
    // set projectiles
    gm->projectiles = NULL;
    
    return 1;
}

void updateGame() {
    gm->level->progress += PROGRESS_RATE;
    
    updatePlayer(gm->player);
    
    if(isMobOnTerrain(*(gm->player),*(gm->level))){
        printf("ouch!\n");
    }
    
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



