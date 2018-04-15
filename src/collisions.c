#include "../include/collisions.h"

int isMobOnTerrain(Mob m, Level l){
    int mapColumn = m.px * l.width;
    int mapRow = m.py * l.height;
    if (l.map[mapRow % l.height][mapColumn % l.width] != 0){
        l.map[mapRow % l.height][mapColumn % l.width] = 0;
        return 1;
    }
    return 0;
}

int isMobOnMob(Mob m1, Mob m2){
    int deltaX = m1.px - m2.px;
    int deltaY = m1.py - m2.py;
    return !deltaX && !deltaY ;
}
