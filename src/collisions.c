#include "../include/collisions.h"

static void setHitbox(char mobType, float *w, float *h) {
    float scale = 1/getLevel().height;
    switch (mobType) {
        case ENEMY:
            *w = scale * ENEMY_W;
            *h = scale * ENEMY_H;
            break;
            
        case PLAYER:
            *w = scale * PLAYER_W;
            *h = scale * PLAYER_H;
            break;
            
        case BONUS:
            *w = scale * BONUS_W;
            *h = scale * BONUS_H;
            break;
            
        case PROJECTILE:
            *w = scale * PROJECTILE_W;
            *h = scale * PROJECTILE_H;
            break;
    }
}

int isMobOnTerrain(Mob m, Level l){
    int col = (int)(m.px * l.width) % l.width ;
    int row = (int)(m.py * l.height) % (l.height-1);
    
    if (l.map[row][col] != 0){
        l.map[row][col] = 0;
        return 1;
    }
    
    else if (l.map[row+1][col] != 0) {
        l.map[row+1][col] = 0;
        return 1;
    }
    
    return 0;
}

int isMobOnMob(Mob m1, Mob m2){
    float m1w, m1h, m2w, m2h;
    setHitbox(m1.type, &m1w, &m1h);
    setHitbox(m2.type, &m2w, &m2h);
    
    int deltaX = m1.px - m2.px;
    int deltaY = m1.py - m2.py;
    return !deltaX && !deltaY ;
}
