#include "../include/terrain.h"

// to be able to see the blocs poping in and out on the left and right borders
#define DEBUG_MARGIN 0

void drawTerrain(Level l, unsigned int vw, unsigned int vh){
    unsigned int stop = l.progress + vw * l.height / vh - DEBUG_MARGIN + 1;
    
    for (unsigned int y = 0; y < l.height; y++)
        for (unsigned int x = l.progress + DEBUG_MARGIN; x <= stop && x < l.width; x++) {
            glPushMatrix();
            glTranslatef(x+0.5,y+0.5,0);
            if (l.map[y][x] != 0) drawSprite(SPRITE_WALL);
            glPopMatrix();
        }
}
