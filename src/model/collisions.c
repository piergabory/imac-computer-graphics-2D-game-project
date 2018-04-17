#include "model/collisions.h"

static void setHitbox(char mobType, float *w, float *h) {
    Level l = getLevel();
    float scalex = 0.5/l.width;
    float scaley = 0.5/l.height;
    
    switch (mobType) {
        case ENEMY:
            *w = scalex * ENEMY_W;
            *h = scaley * ENEMY_H;
            break;
            
        case PLAYER:
            *w = scalex * PLAYER_W;
            *h = scaley * PLAYER_H;
            break;
            
        case BONUS:
            *w = scalex * BONUS_W;
            *h = scaley * BONUS_H;
            break;
            
        case PROJECTILE:
            *w = scalex * PROJECTILE_W;
            *h = scaley * PROJECTILE_H;
            break;
    }
}

int isMobOnTerrain(Mob m, Level l){
    float mw, mh;
    setHitbox(m.type, &mw, &mh);
    
    int minCol = (int)((m.px) * l.width) % l.width;
    int minRow = (int)((m.py - mh) * l.height) % (l.height-1);
    
    int maxCol = (int)((m.px) * l.width) % l.width;
    int maxRow = (int)((m.py + mh) * l.height) % (l.height-1);
    
    if (l.map[minRow][minCol] || l.map[maxRow][maxCol])
        return l.map[minRow][minCol];
    else
        return 0;
}

int isMobOnMob(Mob m1, Mob m2){
    float m1w, m1h, m2w, m2h;
    setHitbox(m1.type, &m1w, &m1h);
    setHitbox(m2.type, &m2w, &m2h);
    
    float deltaPosX = fabs(m1.px - m2.px);
    float deltaPosY = fabs(m1.py - m2.py);
    return deltaPosX < (m1w + m2w) && deltaPosY < (m1h + m2h) ;
}
