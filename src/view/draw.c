#include "view/draw.h"

static void drawMobList(char mob, Level level, int sprite) {
    MobList list = getMobList(mob);
    while (list != NULL) {
        glPushMatrix();
        glTranslatef(list->px * level.width, list->py * level.height,0);
        drawSprite(sprite);
        list = list->next;
        glPopMatrix();
    }
}

/**
 * DRAW LOOP
 * ---------
 * OpenGL code executed between each clearBuffer and swapBuffer.
 */
void draw() {
    Level l = getLevel();
    Mob p = getPlayer();
    
    glPushMatrix();
    glScalef(1.0/l.height, 1.0/l.height, 1.0);
    glTranslatef(-(l.progress * l.width),0,0);
    
    // paint terrain
    drawTerrain(l, getViewportWidth(), getViewportHeight());
    
    // paint player
    glPushMatrix();
    glTranslatef(p.px * l.width, p.py * l.height,0);
    drawSprite(SPRITE_PLAYER + ((int)(l.progress*200)%2));
    glPopMatrix();
    
    // paint mobs (bonus, ennemy, projectile)
    drawMobList(BONUS, l, SPRITE_BONUS);
    drawMobList(ENEMY, l, SPRITE_ENEMY);
    drawMobList(PROJECTILE, l, SPRITE_PROJECTILE);
    drawMobList(ENNEMY_PROJECTILE, l, SPRITE_ENNEMY_PROJECTILE);
    
    glPopMatrix();
    
    int screen = SPRITE_EMPTY;
    switch (l.status) {
        case -1: screen = SPRITE_DEFEAT; break;
        case 1: screen = SPRITE_VICTORY; break;
    }
    
    glPushMatrix();
    
    glTranslatef(0.5*(getViewportWidth()/(float)getViewportHeight()), 0.5, 0);
    glScalef(.9,.9,1);
    
    if (l.status < 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSprite(SPRITE_DEFEAT);
    } else if (l.status > 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSprite(SPRITE_VICTORY);
    }
    
    glPopMatrix();
    
    drawHealthBar(p.health);
}


/**
 * INIT VIEW
 * ----------
 * Initialise view
 */
void initView() {
    initSprites();
    
    // set sky color
    glClearColor(0.3, 0.6, 1.0, 1.0);
    
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
