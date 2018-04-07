#include "../include/flapimac.h"
#include "../include/load.h"
#include <stdio.h>

int initGame() {
    // set player
    player.px = player.py = player.vx = player.vy = 0;
    player.type = PLAYER;
    player.next = NULL;
    
    // set world
    loadWorld("image.ppm", &level, &enemies, &bonuses);
    level.progress = 0;
    
    return 1;
}

void movePlayer(int direction) {
    player.ypos += direction/100;
}
