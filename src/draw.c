#include "../include/draw.h"

/* DRAW LOOP
 * ---------
 * OpenGL code executed between each clearBuffer and swapBuffer.
 */
void draw(Game gm) {
    glPushMatrix();
    glScalef(1.0/gm.level->height, 1.0/gm.level->height, 1.0);
    
    // paint terrain
    glPushMatrix();
    glTranslatef(-(gm.level->progress),0,0);
    drawTerrain(*(gm.level));
    glPopMatrix();
    
    // paint player
    glPushMatrix();
    glTranslatef(gm.player->px * gm.level->width, gm.player->py * gm.level->height,0);
    drawSprite(SPRITE_PLAYER);
    glPopMatrix();
    
    // paint ennemies
    Mob *ennemy = gm.enemies;
    while (ennemy != NULL) {
        glPushMatrix();
        glTranslatef(ennemy->px * gm.level->width - gm.level->progress, ennemy->py * gm.level->height,0);
        drawSprite(SPRITE_ENEMY);
        ennemy = ennemy->next;
        glPopMatrix();
    }
    
    // paint bonuses
    Mob *bonus = gm.bonuses;
    while (bonus != NULL) {
        glPushMatrix();
        glTranslatef(bonus->px * gm.level->width - gm.level->progress, bonus->py * gm.level->height,0);
        drawSprite(SPRITE_BONUS);
        bonus = bonus->next;
        glPopMatrix();
    }
    
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
