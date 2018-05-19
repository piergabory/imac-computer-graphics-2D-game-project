#include "model/updategame.h"

/**
 * Update Player Physics
 * ---------------------
 * updates position with the speed vector
 * updates speed vector with the DRAG value
 *
 * Makes the player bounce on the viewport limits
 *
 * @param Mob *p reference to the player mob structure
 */
void updatePlayer(Mob *p, Level l) {
    int up, down, left, right;
    
    up = getTriggerStatus(UP);
    down = getTriggerStatus(DOWN);
    left = getTriggerStatus(LEFT);
    right = getTriggerStatus(RIGHT);
    
    // stop if no key are pressed
    if (!(up || down || left || right)) {
        p->vy *= 0.1;
        p->vx *= 0.1;
    }
    
    // horizontal speed
    if (up && !down) {
        p->vy = -PLAYER_SPEED / l.height;
    } else if (!up && down) {
        p->vy = PLAYER_SPEED / l.height;
    }
    
    // vertical speed
    if (left && !right) {
        p->vx = -PLAYER_SPEED / l.width;
    } else if (!left && right) {
        p->vx = PLAYER_SPEED / l.width;
    }
    
    
    // position from velocity
    p->px += p->vx + PROGRESS_RATE;
    p->py += p->vy;
    
    // velocity from drag
    p->vx *= DRAG;
    p->vy *= DRAG;
    
    
    // bounce on level left/right borders
    if (p->px > 1 || p->px < 0) {
        p->vx *= -1;
        p->px = roundf(p->px);
    }
    
    // bounce on level top/bottom borders
    if (p->py > 1 || p->py < 0) {
        p->vy *= -1;
        p->py = roundf(p->py);
    }
    
    // player shoot
    if (getTriggerStatus(SPACE)) {
        p->projectile_clock++;
    } else {
        p->projectile_clock = 0;
    }
}


/**
 * Update Ennemy Physics
 * ---------------------
 * IF the enemy is close to the player, move towards him
 * IF the enemy is far away, move predictably
 *
 * Note: enemies only move vertically
 *
 * updates position from speed vector
 *
 * @param Mob *e reference to the enemy structure to update
 * @param Mob p copy of the player structure
 */
void updateEnemy(Mob *e, Mob p) {
    // if enemy close to player
    if (e->px - p.px < 0.1){
        // move velocity vector towards player
        e->vy += ((p.py - e->py) > 0)? 0.0001 : -0.0001;
        e->vy *= DRAG;
    } else {
        // move with a sine-wave pattern
        e->vy += sinf((p.px - e->px)*100)/100000;
    }
    
    e->px += e->vx;
    e->py += e->vy;
}


/**
 * Update (player/enemy) Projectile Physics
 * ----------------------------------------
 * updates projectile position from velocity vector
 *
 * @param Mob *p reference to the projectile structure
 */
void updateProjectile(Mob *p) {
    // position
    p->px += p->vx + PROGRESS_RATE;
    p->py += p->vy;
}
