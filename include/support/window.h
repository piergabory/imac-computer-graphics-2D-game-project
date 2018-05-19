#ifndef window_init_h
#define window_init_h

#include "frameworks.h"
#include "messages.h"

// default screen size
#define WINDOW_DEFAULT_WIDTH    800
#define WINDOW_DEFAULT_HEIGHT   600

// see Update Viewport method
#define UNDEFINED_DIMENTION -1


/**
 *  INIT WINDOW
 *  ---------------
 *  Actions:
 *  - initialise SDL
 *  - create new window
 *  - initialise OpenGL context
 *
 *  @param SDL_Window **win
 *  @param String title, text in the titlebar
 */
int initWindow(SDL_Window **win, char* title);


/**
 *  UPDATE VIEWPORT
 *  ---------------
 *  Handles resizing of the window.
 *
 *  Updates the projection matrix to keep proportions consistent
 *  and scales the space to fit the size of the window.
 *
 *  @param int w, new width
 *  @param int h, new height
 *
 *  Use UNDEFINED_DIMENTION to ignore viewport aspect ratio changes
 */
void updateViewport(int w, int h);


/**
 * @var static unsigned int Window width, viewport's width in pixels
 */
static unsigned int WINDOW_WIDTH = WINDOW_DEFAULT_WIDTH;

/**
 * @var static unsigned int Window height, viewport's height in pixels
 */
static unsigned int WINDOW_HEIGHT = WINDOW_DEFAULT_HEIGHT;



//// GETTERS

/**
 * @return unsigned int viewport's width in pixels
 */
unsigned int getViewportWidth();

/**
 * @return unsigned int viewport's height in pixels
 */
unsigned int getViewportHeight();

/**
 * @return float viewport's aspect ratio
 */
float getAspectRatio();

#endif /* window_init_h */
