#include "model/game.h"

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

    // set mob lists
    gm->enemies = NULL;
    gm->bonuses = NULL;
    gm->projectiles = NULL;
    
    // set level, ennemies and bonuses
    if(loadWorld("map.ppm", gm) != 0){
        printf(ERR_LOADWORLD);
        return 0;
    }
    
    // set player
    gm->player->px = 0.01;
    gm->player->py = 0.5;
    gm->player->vx = 0;
    gm->player->vy = 0;
    
    gm->player->health = 20;
    gm->player->type = PLAYER;
    gm->player->next = NULL;
    return 1;
}

void updateGame() {
    // stop scrolling at the end of the map
    float max_progress = 1 - (getViewportWidth()/(float)getViewportHeight()) * (gm->level->height/(float)gm->level->width);
    if (gm->level->progress < max_progress)
        gm->level->progress += PROGRESS_RATE;

    updatePlayer(gm->player);
    
    // player hit terrain
    int terrainType = 0;
    if((terrainType = isMobOnTerrain(*(gm->player), *(gm->level)))){
        printf("ouch!\n");
        gm->player->vx *= -.5;
        gm->player->vy *= -.5;
        if(terrainType == 18)
            /* TODO : Victory */
            printf("Win");
        else
            playerHealth(WALL_DAMAGE);
    }
    
    // player hit mob
    MobList *curr = &(gm->enemies);
    while (*curr != NULL) {
        if (isMobOnMob(**curr, *(gm->player))) {
            freeMob(curr);
            printf("aie!\n");
            playerHealth(ENEMY_DAMAGE);
        } else {
            updateEnnemy(*curr);
            curr = &((*curr)->next);
        }
    }
    
    // player hit bonus
    curr = &(gm->bonuses);
    while (*curr != NULL) {
        if (isMobOnMob(**curr, *(gm->player))) {
            freeMob(curr);
            printf("yay!\n");
            playerHealth(BONUS_HEALTH);
        } else {
            curr = &((*curr)->next);
        }
    }
    
    // projectiles
    MobList *target;
    curr = &(gm->projectiles);
    while (*curr != NULL) {
        // projectile hit wall
        if (isMobOnTerrain(**curr, *(gm->level)) || (*curr)->px > 1) {
            freeMob(curr);
            
        } else {
            updateProjectile(*curr);
            
            // projectile hit enemy
            target = &(gm->enemies);
            while (*target != NULL && *curr != NULL) {
                if (isMobOnMob(**target, **curr)) {
                    freeMob(target);
                    freeMob(curr);
                    printf("pow!\n");
                    break;
                } else {
                    target = &((*target)->next);
                }
            }
            
            if (*curr != NULL) curr = &((*curr)->next);
        }
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

void playerHealth(int value) {
    if ((gm->player->health + value) < 0) {
        printf("game over\n");
        /*
         TODO : Game over.
         */
    } else {
        gm->player->health += value;
    }
}

