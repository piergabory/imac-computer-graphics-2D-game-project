#ifndef draw_h
#define draw_h

#include "model/game.h"
#include "support/window.h"

#include "sprites.h"
#include "terrain.h"
#include "gui.h"


/* INIT VIEW
 * ----------
 * Initialise view
 *
 * @param: sdl window (see window.h)
 *
 * the loop method is called until it returns false (0)
 */
void initView();

/* DRAW LOOP
 * ---------
 * OpenGL code executed between each clearBuffer and swapBuffer.
 */
void draw();

void setScreen(int screenId);

static int screen = SPRITE_EMPTY;

#endif /* draw_h */
