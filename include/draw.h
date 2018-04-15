#ifndef draw_h
#define draw_h

#include "game.h"
#include "window.h"
#include "sprites.h"
#include "terrain.h"


/* INIT VIEW
 * ----------
 * Initialise view
 *
 * @param: sdl window (see window.h)
 *
 * the loop method is called until it returns false (0)
 */
void initView();

static void drawMobList();

/* DRAW LOOP
 * ---------
 * OpenGL code executed between each clearBuffer and swapBuffer.
 */
void draw(Game gm);

#endif /* draw_h */
