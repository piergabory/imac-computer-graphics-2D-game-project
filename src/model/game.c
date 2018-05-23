#include "model/game.h"

//// GETTERS

/**
 * Level Getter
 * @return Level of the active game structure
 */
Level getLevel() {return *(gm->level); }


/**
 * Player mob Getter
 * @return Mob of the player in the active game structure
 */
Mob getPlayer() { return *(gm->player); }


/**
 * Mob List Getter
 * @param char Mobtype (defined in model/structs/mob.struct.h)
 * @return MobList of selected type, from the active game structure
 */
MobList getMobList(MobType type) {
    switch (type) {
        case ENEMY: return gm->enemies;
        case BONUS_HEALTH:
        case BONUS_WEAPON:
        case BONUS_SPEED:
            return gm->bonuses;
        case PROJECTILE: return gm->projectiles;
        case ENEMY_PROJECTILE: return gm->enemy_projectiles;
        case PLAYER: return gm->player;
    }
}




//// GAME METHODS

/**
 * Initialise Game
 * ---------------
 * Set the game structure to its sarting state
 * @return int success status boolean
 */
int initGame() {
    // set random seed
    srand(time(NULL));
    
    // allocate game structure
    gm = allocGame();

    
    // initialize mob lists
    gm->enemies = NULL;
    gm->bonuses = NULL;
    
    
    // set level, ennemies and bonuses data
    if(loadWorld("map.ppm", gm) != 0){
        printf(ERR_LOADWORLD);
        return 0;
    }
    
    // initialise projectiles lists
    gm->projectiles = NULL;
    gm->enemy_projectiles = NULL;
    
    // initialize level status to 'playing'
    gm->level->status = PLAYING;
    
    
    // -- initialise player
    
    // set player default position
    gm->player->px = 0.05;
    gm->player->py = 0.5;
    
    // velocity vector
    gm->player->vx = 0;
    gm->player->vy = 0;
    
    gm->player->health = PLAYER_STARTING_HEALTH;
    gm->player->type = PLAYER;
    gm->player->next = NULL;
    gm->player->max_speed = PLAYER_DEFAULT_SPEED;
    
    return 1;
}


/**
 * Reset Game
 * ----------
 * 1. De-allocate active game structure off memory
 * 2. initialise a new one.
 */
void resetGame() {
    freeGame(gm);
    initGame();
}


/**
 * Update Game
 * -----------
 * Controls the frame's computations for
 *    - Collisions
 *    - Physics
 *    - Player/Game Status/Progress/health
 *
 * Should be called in the SDL main loop
 */
void updateGame() {
    if (gm->level->status != PLAYING) return; 
    
    float level_screen_size = (getViewportWidth() / (float)getViewportHeight()) * gm->level->height;
    float zone_size = level_screen_size / (float)gm->level->width;
    
    // stop scrolling at the end of the map
    if (gm->level->progress < 1 - zone_size)
        gm->level->progress += PROGRESS_RATE;
    
     // player shoot if is shooting
    if (gm->player->projectile_clock % gm->player->reload_time == 1) {
        playerShoot();
        gm->player->projectile_clock ++;
    }
    
    // update player
    updatePlayer(gm->player, gm->level);

    
    // Bonus, Enemy and Enemy Projectile
    playerHit(&(gm->bonuses));
    playerHit(&(gm->enemies));
    playerHit(&(gm->enemy_projectiles));
    
    //// END PLAYER COLLISIONS

    
    //// UPDATE MOBS
    MobList *curr = NULL;
    MobList *target = NULL;
    
    
    for (curr = &(gm->enemies); *curr != NULL; curr = &((*curr)->next)) {
        if(isHidden(**curr)) continue;
        
        updateEnemy(*curr, *(gm->player));
        
        if (isMobOnTerrain(**curr, *(gm->level))) {
            (*curr)->vx *= -1;
            (*curr)->vy *= -1;
        }
        
        // ennemy shoot randomly if align with the player and is visible
        if ((rand() % 300) == 0 && fabs((*curr)->py - gm->player->py) < 0.1) {
            enemyShoot(**curr);
        }
    }
    
    // enemy projectiles
    curr = &(gm->enemy_projectiles);
    while (*curr != NULL) {
        updateProjectile(*curr);
    
        // delete projectile out of the screen
        if (isHidden(**curr)) {
            freeMob(curr);
        } else {
            curr = &((*curr)->next);
        }
    }
    
    // projectiles
    curr = &(gm->projectiles);
    while (*curr != NULL) {
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
        
        // if projectile left the frame, delete it
        if (isHidden(**curr)) {
            freeMob(curr);
        } else {
            curr = &((*curr)->next);
        }
    }
}




//// PLAYER METHODS

/**
 * Player Hit
 * ----------
 * Checks if the player has hit a mob in a given mob collection
 * if so applies damage (or health bonus) to the player and kills the mob
 *
 * @param MobList *ml, reference to the collections of mobs to check
 * @param int damage, value added to the player's health on collision
 *      -> Mob damage is defined above
 */
void playerHit(MobList *ml) {
    MobList *hit = isMobOnMoblist(*(gm->player), ml);
    if(*hit != NULL) {
        switch ((*hit)->type) {
            case ENEMY:
                playerHealth(ENEMY_DMG);
                break;
                
            case ENEMY_PROJECTILE:
                playerHealth(ENEMY_PROJECTILE_DMG);
                break;
                
            case BONUS_HEALTH:
                playerHealth(BONUS_DMG);
                break;
                
            case BONUS_SPEED:
                gm->player->max_speed *= SPEED_BUFF;
                break;
                
            case BONUS_WEAPON:
                // one chance over three to have more bullets or faster reload speed
                if (rand()%3)
                    gm->player->reload_time /= WEAPON_BUFF;
                else
                    gm->player->bullet_count++;
                break;
                
            case PLAYER:
            case PROJECTILE:
                // do nothing
                break;
        }
        freeMob(hit);
    }
}


/**
 * Player Shoot
 * ------------
 * Spawns a player projectile on the player, with a fixed X velocity.
 */
void playerShoot() {
    float angle = 0;
    float speed = 0;
    float vx = 0;
    float vy = 0;
    
    // for each bullet
    for (unsigned int i = 0; i < gm->player->bullet_count; i++){
        
        // compute a different spread and speed for each bullet
        angle = i/(float)gm->player->bullet_count;
        speed = PLAYER_DEFAULT_SPEED * (1.01 - angle/10.0);
        
        vx = speed / gm->level->height;
        vy = speed * angle / gm->level->height;
        
        newMob(&(gm->projectiles), PROJECTILE, gm->player->px, gm->player->py, vx, vy);
        newMob(&(gm->projectiles), PROJECTILE, gm->player->px, gm->player->py, vx, -vy);
    }
}


/**
 * Player Health
 * -------------
 * Updates the player's health
 * Set game status to 'game over' if health reaches 0
 *
 * @param int health increment
 */
void playerHealth(Damage value) {
    if ((gm->player->health + value) < 0) {
        gm->level->status = GAME_OVER;
    } else {
        gm->player->health += value;
    }
}





/**
 * Ennemy Shoot
 * ------------
 * Spawns an ennemy projectile on a mob, with a fixed negative X velocity.
 * @param Mob e (ennemy), projectile source.
 */
void enemyShoot(Mob e) {
    newMob(
           // type
           &(gm->enemy_projectiles),  // list
           ENEMY_PROJECTILE,      // type
           
           // position
           e.px,
           e.py,
           
           // velocity vector
           -(0.001 + e.vx),
           0
           );
}


/**
 * Is Mob Hidden
 * -------------
 * Tells if Mobs are on the viewport or not.
 * out of frame mobs should not be drawn or computed in collisions and physics updates.
 *
 * @param Mob m (mob) to check.
 * @return int 0 if in frame, 1 if out of bounds
 */
int isHidden(Mob m) {
    float level_screen_size = (getViewportWidth()/(float)getViewportHeight()) * gm->level->height;
    float zone_size = level_screen_size/(float)gm->level->width;
    
    // mob is off the left bound of the viewport
    int isAfter = m.px < gm->level->progress;
    
    // mob is off the right bound of the viewports
    int isBefore = m.px > gm->level->progress + zone_size;
    
    return isBefore || isAfter;
}

