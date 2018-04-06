#ifndef window_init_h
#define window_init_h

#include "frameworks.h"
#include "messages.h"


#define WINDOW_DEFAULT_WIDTH    200
#define WINDOW_DEFAULT_HEIGHT   200


/*  INIT WINDOW
 *  ---------------
 *  @params: window reference, window title (text in the titlebar)
 *
 *  Actions:
 *  - initialise SDL
 *  - create new window
 *  - initialise OpenGL context
 */
int initWindow(SDL_Window **win, char* title);


/*  UPDATE VIEWPORT
 *  ---------------
 *  Handles resizing of the window.
 *
 *  Updates the projection matrix to keep proportions consistent
 *  and scales the space to fit the size of the window.
 */
void updateViewport();


// window dimentions:
static unsigned int WINDOW_WIDTH = WINDOW_DEFAULT_WIDTH;
static unsigned int WINDOW_HEIGHT = WINDOW_DEFAULT_HEIGHT;

#endif /* window_init_h */
