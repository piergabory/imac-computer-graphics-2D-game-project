#ifndef draw_h
#define draw_h

#include <math.h>

#include "model/game.h"
#include "support/window.h"

#include "sprites.h"
#include "terrain.h"
#include "gui.h"

#define PI 3.141592654

/**
 * INIT VIEW
 * ----------
 * Initialise the view
 *
 * Set the clearing color and enable transparency
 */
void initView();

/**
 * DRAW LOOP
 * ---------
 * Code executed between clear and swap of the buffer
 */
void draw();

#endif /* draw_h */
