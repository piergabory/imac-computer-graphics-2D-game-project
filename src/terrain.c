#include "../include/terrain.h"

#define TERRAIN_TEX "../textures/wall.png"

static GLuint terrainSprite;

void drawTerrain(World map){
    // save original view matrix
    glPushMatrix();
    glScalef(1.0/map.width, 1.0/map.height, 1.0);
         glCallList(terrainSprite);
    if (!terrainSprite) terrainSprite = getSpriteGlu(TERRAIN_TEX);
    
    for (int x = 0; x < map.width; x++) {
        for (int y = 0; y < map.height; y++) {
            glPushMatrix();
            glTranslatef(x,y,0);
        
            if (map.data[y][x] != 0)
                glCallList(terrainSprite);
        
            glPopMatrix();
        }
    }
                             
    
    // restore view matrix
    glPopMatrix();
}
