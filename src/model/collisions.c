// include header
#include "model/collisions.h"

/**
 * Set Hit Box
 * -----------
 * set given values to mob's hitbox dimentions
 * Static method
 *
 * @param char mobType, type of the mob
 *
 * @param float *w, pointer to the width value adress
 * @param float *h, pointer to the height value adress
 */
static void setHitbox(char mobType, float *w, float *h) {
    Level l = getLevel();
    float scalex = 0.5/l.width;
    float scaley = 0.5/l.height;
    
    switch (mobType) {
        case ENEMY:
            *w = scalex * 1;
            *h = scaley * 1;
            break;
            
        case PLAYER:
            *w = scalex * 1;
            *h = scaley * 1;
            break;
            
        case BONUS:
            *w = scalex * 0.6;
            *h = scaley * 0.6;
            break;
            
        case PROJECTILE:
            *w = scalex * 0.4;
            *h = scaley * 0.2;
            break;
            
        case ENEMY_PROJECTILE:
            *w = scalex * 0.4;
            *h = scaley * 0.2;
            break;
    }
}


/**
 * IS Mob On Terrain
 * -----------------
 * Get the terrain type if the mob is hitting the ground.
 * 0 if still flying fine.
 *
 * @param Mob m, the mob to check
 * @param Level l, the terrain mob might be crashing into
 *
 * @return int terrain type, 0 if no collisions
 */
TerrainType isMobOnTerrain(Mob m, Level l) {
    float mw, mh;
    setHitbox(m.type, &mw, &mh);
    
    int minCol = (int)((m.px) * l.width) % l.width;
    int minRow = (int)((m.py - mh) * l.height) % (l.height-1);
    
    int maxCol = (int)((m.px) * l.width) % l.width;
    int maxRow = (int)((m.py + mh) * l.height) % (l.height-1);
    
    if (l.map[maxRow][maxCol] == FINISH_LINE || l.map[minRow][maxCol] == FINISH_LINE) {
        return FINISH_LINE;
    }
    
    if (l.map[minRow][minCol] || l.map[maxRow][maxCol] || l.map[minRow][maxCol] || l.map[maxRow][minCol]) {
        return OBSTACLE;
    }
    
    else
        return VOID;
}


/**
 * IS Mob On Mob
 * -------------
 * Check if two mobs are colliding each other
 *
 * @param Mob m1, first mob
 * @param Mob m2, second mob
 *
 * @return Int boolean (0 or 1) if m1's hitbox overlaps m2's
 */
int isMobOnMob(Mob m1, Mob m2) {
    float m1w, m1h, m2w, m2h;
    setHitbox(m1.type, &m1w, &m1h);
    setHitbox(m2.type, &m2w, &m2h);
    
    // get distance between mobs
    float deltaPosX = fabs(m1.px - m2.px);
    float deltaPosY = fabs(m1.py - m2.py);
    
    // check if distance between mobs is larger than the mob size
    return deltaPosX < (m1w + m2w) && deltaPosY < (m1h + m2h) ;
}


/**
 * IS Mob On Mob List
 * ------------------
 * Check if a mob is hitting at least one other mob out of a collection of mobs.
 *
 * @param Mob m, mob to check
 * @param MobList *ml, reference to the collection of mobs
 *
 * @return MobList *mob, reference to the MobList referencing to the hitted mob
 * @return NULL if no collisions
 */
MobList *isMobOnMoblist(Mob m, MobList *ml) {
    if(ml != NULL) {
        while (*ml != NULL) {
            if (isMobOnMob(**ml, m))
                break;
            else
                ml = &((*ml)->next);
        }
    }
    return ml;
}
