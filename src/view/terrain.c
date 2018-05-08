#include "view/terrain.h"

// > 0 to be able to see the blocs poping in and out on the left and right borders
#define DEBUG_MARGIN 0

/**
 * Draw Terrain
 * ------------
 * Displays the world.
 *
 * @param Level l, world to display
 * @param unsigned int vw, viewport width in pixels
 * @param unsigned int vh, viewport height in pixels
 */
void drawTerrain(Level l, unsigned int vw, unsigned int vh){
    // compute the index of the first row to be drawn from the level map
    unsigned int start = l.progress * l.width + DEBUG_MARGIN;
    
    // compute the maximum numbers of columns to be drawn from the level map.
    unsigned int stop = l.progress * l.width + vw * l.height / vh - DEBUG_MARGIN + 1;
    
    
    // for each row of the map
    for (unsigned int y = 0; y < l.height; y++) {
        // and each column available
        for (unsigned int x = start; x <= stop && x < l.width; x++) {
            glPushMatrix();
            
            // move to the terrain bloc position
            glTranslatef(x+0.5,y+0.5,0);
            
            // draw terrain sprite
            if (l.map[y][x] != 0) {
                    drawSprite(l.map[y][x]-1);
            }
            
            glPopMatrix();
        }
    }
}
