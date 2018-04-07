#include "../include/flapimac.h"
#include "../include/load.h"
#include <stdio.h>

int initGame() {
    // set player
    player.xpos = 0;
    player.ypos = 0;
    player.type = PLAYER;
    player.next = NULL;
    
    // set world
    loadWorld("image.ppm", &obstacleMap, &enemies, &bonuses);
    obstacleMap.progress = 0;
    
    return 1;
}

void movePlayer(int direction) {
    player.ypos += direction/100;
}
