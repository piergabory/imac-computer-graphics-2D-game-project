#include "../include/flapimac.h"
#include "../include/load.h"
#include <stdio.h>
#include <math.h>

#define MAX_SPEED 1
#define DRAG 0.95

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

void updateGame() {
    // position
    player.px += player.vx;
    player.py += player.vy;
    
    // drag
    player.vx *= DRAG;
    player.vy *= DRAG;
    
    
    // bounce on borders
    if (player.px > 1 || player.px < 0) {
        player.vx *= -1;
        player.px = roundf(player.px);
    }
    
    if (player.py > 1 || player.py < 0) {
        player.vy *= -1;
        player.py = roundf(player.py);
    }
}

void changePlayerXYSpeedBy(float vx, float vy) {
    if (fabs(player.vx + vx) < MAX_SPEED) player.vx += vx;
    if (fabs(player.vy + vy) < MAX_SPEED) player.vy += vy;
}
