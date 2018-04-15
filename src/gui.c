#include "../include/gui.h"

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
