#include "view/draw.h"

/**
 * Draw Mob List
 * -------------
 * draws sprites for each mobs of a list design by it's type.
 */
static void drawMobList(MobType type, Level level) {
    MobList ml = getMobList(type);
    
    Sprite sprite;
    SpriteAlt alt;
    
    while (ml != NULL) {
        getSprite(ml->type, &sprite, &alt);
        
        glPushMatrix();
        glTranslatef(ml->px * level.width, ml->py * level.height,0);
        drawSprite(sprite + ((int)(level.progress * 200) % alt));
        glPopMatrix();
        
        ml = ml->next;
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
    glTranslatef(-l.progress * l.width, 1, 0);
    
    
    // paint terrain
    drawTerrain(l);
    
    glTranslatef(0, -1, 0);
    
    // paint player
    glPushMatrix();
    glTranslatef(p.px * l.width, p.py * l.height,0);
    drawSprite(SPRITE_PLAYER + ((int)(l.progress*200)%2));
    glPopMatrix();
    
    // paint mobs (bonus, ennemy, projectile)
    drawMobList(BONUS_HEALTH, l);
    drawMobList(ENEMY, l);
    drawMobList(PROJECTILE, l);
    drawMobList(ENEMY_PROJECTILE, l);
    
    // restore view matrix
    glPopMatrix();
    
    // health bar
    drawAppropriateScreen(l.status);
    drawHealthBar(p.health);
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
