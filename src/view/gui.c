#include "view/gui.h"

/**
 * Draw Health Bar
 * ---------------
 * Print health bar on the top left of the screen
 * A line of @var int health bonus sprites
 */
void drawHealthBar(int health) {
    glPushMatrix();
    glScalef(32.0/getViewportHeight(), 32.0/getViewportHeight(), 1);
    glTranslatef(0,1,0);
    for (int i = 0; i < health; i++) {
        glTranslatef(1,0,0);
        drawSprite(SPRITE_BONUS_HEALTH);
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
    glScalef(getAspectRatio(), 1, 1);
    
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
    
    else {
        drawScreen(SCREEN_OVERLAY);
    }
    
    // restore view matrix
    glPopMatrix();
}
