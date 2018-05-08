#include "view/gui.h"

/**
 * Draw Health Bar
 * ---------------
 * Print health bar on the top left of the screen
 * A line of @var int health bonus sprites
 */
void drawHealthBar(int health) {
    glPushMatrix();
    glScalef(16.0/getViewportHeight(), 16.0/getViewportHeight(), 1);
    glTranslatef(0,1,0);
    for (int i = 0; i < health; i++) {
        glTranslatef(1.2,0,0);
        drawSprite(SPRITE_BONUS);
    }
    glPopMatrix();
}
