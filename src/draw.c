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
    
    drawMobList(gm.bonuses, gm.level, SPRITE_BONUS);
    drawMobList(gm.enemies, gm.level, SPRITE_ENEMY);
    drawMobList(gm.projectiles, gm.level, SPRITE_PROJECTILE);
    
    glPopMatrix();
}

static void drawMobList(MobList list, Level level, int sprite) {
    while (list != NULL) {
        glPushMatrix();
        glTranslatef(list->px * level.width - level.progress, list->py * level.height,0);
        drawSprite(sprite);
        list = list->next;
        glPopMatrix();
    }
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
    glClearColor(0.0, 0.0, 0.1, 1.0);
    
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
