#include "../include/terrain.h"

void drawTerrain(World map){
    for (int x = 0; x < map.width; x++) {
        for (int y = 0; y < map.height; y++) {
            glPushMatrix();
            glTranslatef(x+0.5,y+0.5,0);
        
            if (map.data[y][x] != 0)
                drawSprite(SPRITE_WALL);
        
            glPopMatrix();
        }
    }
}
