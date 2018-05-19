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

/**
 * Draws appropriate screen depending on gamestate
 */
void drawAppropriateScreen(GameStatus status) {
    // save view matrix
    glPushMatrix();
    
    // print screen
    glTranslatef(0.5 * getAspectRatio(), 0.5, 0);
    
    // if GAME OVER
    if (status == GAME_OVER) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawScreen(SCREEN_GAME_OVER);
    }
    
    // IF LEVEL COMPLETE
    else if (status == LEVEL_COMPLETE) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawScreen(SCREEN_LEVEL_COMPLETE);
    }
    
    // restore view matrix
    glPopMatrix();
}
