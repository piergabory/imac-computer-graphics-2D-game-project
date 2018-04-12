#ifndef events_h
#define events_h

#include "window.h"
#include "game.h"

/* EVENT LOOP
 * ----------
 * SDL event loop handler
 * Asks SDL for any events and handles them accordingly
 *
 * - QUIT: set loopStatus to 0 so the main loop stops and the program ends.
 * - WINDOW IS RESIZED: collects new width and height and update the window (see window.h)
 */
int eventLoop(Mob *player);

#endif /* events_h */
