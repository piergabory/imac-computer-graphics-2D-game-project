#include "view/draw.h"

/**
 * Draw Mob List
 * -------------
 * draws sprites for each mobs of a list design by it's type.
 */
static void drawMobList(char mob, Level level, int sprite, int alternatives) {
    MobList list = getMobList(mob);
    
    while (list != NULL) {
        glPushMatrix();
        glTranslatef(list->px * level.width, list->py * level.height,0);
        drawSprite(sprite + ((int)(level.progress * 200) % alternatives));
        list = list->next;
        glPopMatrix();
    }
}

/**
 * DRAW LOOP
 * ---------
 * Code executed between clear and swap of the buffer
 */
void draw() {
    // Get copies of the current level and player
    Level l = getLevel();
    Mob p = getPlayer();
    
    // save view matrix state
    glPushMatrix();
    
    // set scale relative to the world dimensions so the world height should fit the screen.
    glScalef(1.0/l.height, 1.0/l.height, 1.0);
    
    // move the viewport relative to the progress value
    glTranslatef(-(l.progress * l.width) + 0.5, 0.5, 0);
    
    
    // paint terrain
    drawTerrain(l, getViewportWidth(), getViewportHeight());
    
    glTranslatef(0, -1, 0);
    
    // paint player
    glPushMatrix();
    glTranslatef(p.px * l.width, p.py * l.height,0);
    drawSprite(SPRITE_PLAYER + ((int)(l.progress*200)%2));
    glPopMatrix();
    
    // paint mobs (bonus, ennemy, projectile)
    drawMobList(BONUS, l, SPRITE_BONUS, SPRITE_BONUS_ALT_COUNT);
    drawMobList(ENEMY, l, SPRITE_ENEMY, SPRITE_ENEMY_ALT_COUNT);
    drawMobList(PROJECTILE, l, SPRITE_PROJECTILE, SPRITE_PROJECTILE_ALT_COUNT);
    drawMobList(ENEMY_PROJECTILE, l, SPRITE_ENEMY_PROJECTILE, SPRITE_ENEMY_PROJECTILE_ALT_COUNT);
    
    // restore view matrix
    glPopMatrix();
    
    // health bar
    drawHealthBar(p.health);
    
    // save view matrix
    glPushMatrix();
    
    // scale the screen overlay to fill the screen
    glTranslatef(0.5*(getViewportWidth()/(float)getViewportHeight()), 0.5, 0);
    glScalef(.9,.9,1);

    // print screen
    
    // if GAME OVER
    if (l.status < 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSprite(SPRITE_DEFEAT);
    }
    
    // IF LEVEL COMPLETE
    else if (l.status > 0) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawSprite(SPRITE_VICTORY);
    }
    
    // restore view matrix
    glPopMatrix();
}


/**
 * INIT VIEW
 * ----------
 * Initialise the view
 *
 * Set the clearing color and enable transparency
 */
void initView() {
    
    // prepare textures
    initSprites();
    
    // set sky color
    glClearColor(0.3, 0.6, 1.0, 1.0);
    
    // enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
