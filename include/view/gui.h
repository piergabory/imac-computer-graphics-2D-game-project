#ifndef gui_h
#define gui_h

#include "view/sprites.h"
#include "support/window.h"
#include "model/structs/level.struct.h"

/**
 * Draw Health Bar
 * ---------------
 * Print health bar on the top left of the screen
 * A line of @var int health bonus sprites
 */
void drawHealthBar(int health);


/**
 * Draws appropriate screen depending on gamestate
 */

void drawAppropriateScreen(GameStatus status);
#endif /* gui_h */
