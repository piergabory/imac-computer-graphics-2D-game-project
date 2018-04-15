#include "../include/collisions.h"

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
    int deltaX = m1.px - m2.px;
    int deltaY = m1.py - m2.py;
    return !deltaX && !deltaY ;
}
