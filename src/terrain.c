#include "../include/terrain.h"

void drawTerrain(Level l){
    for (unsigned int y = 0; y < l.height; y++)
        for (unsigned int x = 0; x < l.width; x++) {
            glPushMatrix();
            glTranslatef(x+0.5,y+0.5,0);
            if (l.map[y][x] != 0) drawSprite(SPRITE_WALL);
            glPopMatrix();
        }
}
