#include "../include/draw.h"

/* DRAW LOOP
 * ---------
 * OpenGL code executed between each clearBuffer and swapBuffer.
 */
void draw(Game gm) {
    glPushMatrix();
    glScalef(1.0/gm.level->width, 1.0/gm.level->height, 1.0);
    
    // paint terrain
    glPushMatrix();
    glTranslatef(-(gm.level->progress+=0.001),0,0);
    drawTerrain(*(gm.level));
    glPopMatrix();
    
    // paint player
    glTranslatef(gm.player->px * gm.level->width, gm.player->py * gm.level->height,0);
    drawSprite(SPRITE_PLAYER);
    
    glPopMatrix();
}

/* INIT VIEW
 * ----------
 * Initialise view
 *
 * @param: sdl window (see window.h)
 *
 * the loop method is called until it returns false (0)
 */
void initView() {
    initSprites();
    
    // set sky color
    glClearColor(0.5, 0.7, 1.0, 1.0);
    
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
