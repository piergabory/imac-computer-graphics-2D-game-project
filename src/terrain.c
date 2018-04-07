#include "../include/terrain.h"

void drawTerrain(Level l){
    for (int x = 0; x < l.width; x++) {
        for (int y = 0; y < l.height; y++) {
            glPushMatrix();
            glTranslatef(x+0.5,y+0.5,0);
        
            if (l.map[y][x] != 0)
                drawSprite(SPRITE_WALL);
        
            glPopMatrix();
        }
    }
}
