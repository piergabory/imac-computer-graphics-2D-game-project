#include "view/terrain.h"

// to be able to see the blocs poping in and out on the left and right borders
#define DEBUG_MARGIN 0

void drawTerrain(Level l, unsigned int vw, unsigned int vh){
    unsigned int stop = l.progress * l.width + vw * l.height / vh - DEBUG_MARGIN + 1;
    unsigned int top, left, bottom, right;
    
    for (unsigned int y = 0; y < l.height; y++)
        for (unsigned int x = l.progress * l.width + DEBUG_MARGIN; x <= stop && x < l.width; x++) {
            glPushMatrix();
            glTranslatef(x+0.5,y+0.5,0);
            if (l.map[y][x] != 0) {
                if (x > 0 && x < l.width-1 && y > 0 && y < l.height - 1) {
                    
                    top = l.map[y+1][x] != 0;
                    left = l.map[y][x+1] != 0;
                    bottom = l.map[y-1][x] != 0;
                    right = l.map[y][x-1] != 0;
                    
                    if (top && left && !right && !bottom)
                        drawSprite(SPRITE_CORNER_TOP_LEFT);
                    
                    else if (!top && left && !right && bottom)
                        drawSprite(SPRITE_CORNER_BOTTOM_LEFT);
                    
                    else if (!top && !left && right && bottom)
                        drawSprite(SPRITE_CORNER_BOTTOM_RIGHT);
                    
                    else if (top && !left && right && !bottom)
                        drawSprite(SPRITE_CORNER_TOP_RIGHT);
                    else
                        drawSprite(SPRITE_WALL);
                } else
                    drawSprite(SPRITE_WALL);
            }
            glPopMatrix();
        }
}
