#ifndef obstacles_h
#define obstacles_h

#include <math.h>

#include "model/game.h"
#include "view/sprites.h"


/**
 * Draw Terrain
 * ------------
 * Displays the world.
 *
 * @param Level l, world to display
 * @param unsigned int vw, viewport width in pixels
 * @param unsigned int vh, viewport height in pixels
 */
void drawTerrain(Level l, unsigned int vw, unsigned int vh);

#endif /* obstacles_h */
