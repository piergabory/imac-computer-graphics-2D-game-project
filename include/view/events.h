#ifndef events_h
#define events_h

#include "support/window.h"
#include "model/game.h"

/**
 * EVENT LOOP
 * ----------
 * SDL event loop handler
 * Asks SDL for any events and handles them accordingly
 *
 * - KEYDOWN : Call game methods according to the pressed key.
 * - QUIT: set loopStatus to 0 so the main loop stops and the program ends.
 * - WINDOW IS RESIZED: collects new width and height and update the window (see window.h)
 *
 * @return int code
 */
int eventLoop();

#endif /* events_h */
