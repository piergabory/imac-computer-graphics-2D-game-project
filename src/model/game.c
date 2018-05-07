#include "model/game.h"

Level getLevel() {return *(gm->level); }

Mob getPlayer() { return *(gm->player); }

MobList getMobList(char mob) {
    switch (mob) {
        case 'e': return gm->enemies;
        case 'b': return gm->bonuses;
        case 'j': return gm->projectiles;
        case 't': return gm->ennemyProjectiles;
        case 'p': return gm->player;
        default: return NULL;
    }
}

int initGame() {
    srand(time(NULL));
    gm = allocGame();

    // set mob lists
    gm->enemies = NULL;
    gm->bonuses = NULL;
    gm->projectiles = NULL;
    gm->ennemyProjectiles = NULL;
    
    // set level, ennemies and bonuses
    if(loadWorld("map.ppm", gm) != 0){
        printf(ERR_LOADWORLD);
        return 0;
    }
    
    gm->level->status = 0;
    
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

void resetGame() {
    freeGame(gm);
    initGame();
}

void updateGame() {
    float level_screen_size = (getViewportWidth()/(float)getViewportHeight()) * gm->level->height;
    float zone_size = level_screen_size/(float)gm->level->width;
    
    // stop scrolling at the end of the map
    if (gm->level->progress < 1 - zone_size)
        gm->level->progress += PROGRESS_RATE;

    // update player
    updatePlayer(gm->player);
    
    //// PLAYER COLLISIONS
    
    // Terrain
    int terrainType = isMobOnTerrain(*(gm->player), *(gm->level));
    if(terrainType != 0){
        printf("ouch!\n");
        gm->player->vx *= -.5;
        if (gm->player->vx >= 0)
            gm->player->vx -= 2*PROGRESS_RATE;
        
        gm->player->vy *= -.5;
        if(terrainType == 18)
            gm->level->status = 1;
        else
            playerHealth(WALL_DAMAGE);
    }
    
    // player cant leave the screen.
    if (gm->player->px < gm->level->progress) gm->player->px = gm->level->progress;
    
    // Bonus, Enemy and Enemy Projectile
    playerHit(&(gm->bonuses), BONUS_HEALTH);
    playerHit(&(gm->enemies), ENEMY_DAMAGE);
    playerHit(&(gm->ennemyProjectiles), PROJECTILE_DAMAGE);

    
    //// END PLAYER COLLISIONS
    
    //// UPDATE MOBS
    MobList *curr = NULL;
    MobList *target = NULL;
    
    
    for (curr = &(gm->enemies); *curr != NULL; curr = &((*curr)->next)) {
        if(isHidden(**curr)) continue;
        
        updateEnnemy(*curr, *(gm->player));
        
        // ennemy shoot randomly if align with the player and is visible
        if ((rand() % 300) == 0 && fabs((*curr)->py - gm->player->py) < 0.1) {
            ennemyShoot(**curr);
        }
    }
    
    for (curr = &(gm->ennemyProjectiles); *curr != NULL; curr = &((*curr)->next)) {
        if(isHidden(**curr)) continue;
        updateProjectile(*curr);
    }
    
    // projectiles
    for (curr = &(gm->projectiles); *curr != NULL; curr = &((*curr)->next)) {
        // projectile is flying
        updateProjectile(*curr);
        
        // projectile hit wall
        if (isMobOnTerrain(**curr, *(gm->level)) || isHidden(**curr)) {
            freeMob(curr);
            break;
        }
            
        // projectile hit enemy
        if (*(target = isMobOnMoblist(**curr, &(gm->enemies))) != NULL) {
            freeMob(target);
            freeMob(curr);
            break;
        }
    }
}

void playerHit(MobList *ml, int damage) {
    MobList *hit = isMobOnMoblist(*(gm->player), ml);
    if(*hit != NULL) {
        freeMob(hit);
        playerHealth(damage);
    }
}

void playerShoot() {
    Mob *tmp = gm->projectiles;
    gm->projectiles = allocMob(PROJECTILE, gm->player->px, gm->player->py);
    gm->projectiles->next = tmp;
    gm->projectiles->vx = 0.001;
}

void ennemyShoot(Mob e) {
    Mob *tmp = gm->ennemyProjectiles;
    gm->ennemyProjectiles = allocMob(ENNEMY_PROJECTILE, e.px, e.py);
    gm->ennemyProjectiles->next = tmp;
    gm->ennemyProjectiles->vx = -0.001;
}

void changePlayerSpeedBy(float vx, float vy) {
    if (fabs(gm->player->vx + vx) < MAX_SPEED) gm->player->vx += vx;
    if (fabs(gm->player->vy + vy) < MAX_SPEED) gm->player->vy += vy;
}

void playerHealth(int value) {
    if ((gm->player->health + value) < 0) {
        gm->level->status = -1;
    } else {
        gm->player->health += value;
    }
}

int isHidden(Mob m) {
    float level_screen_size = (getViewportWidth()/(float)getViewportHeight()) * gm->level->height;
    float zone_size = level_screen_size/(float)gm->level->width;
    
    // mob is off the left bound of the viewport
    int isAfter = m.px < gm->level->progress;
    
    // mob is off the right bound of the viewports
    int isBefore = m.px > gm->level->progress + zone_size;
    
    return isBefore || isAfter;
}

