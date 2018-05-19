#include "support/window.h"

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
int initWindow(SDL_Window **win, char* title) {
    // initialize SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, ERR_SDL_INIT);
        return 0;
    }
    
    // create window
    *win = NULL;
    *win = SDL_CreateWindow(
      title,                                            // titlebar text
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // x/y coordinates for window on screen (top/right corner)
      WINDOW_WIDTH,WINDOW_HEIGHT,                       // window size
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL          // fullscreen or resizable mode
    );
    
    // check for errors
    if(*win == NULL) {
        fprintf(stderr, ERR_WINDOW_INIT);
        return 0;
    }
    
    // initialize window
    SDL_GL_CreateContext(*win);
    updateViewport(UNDEFINED_DIMENTION,UNDEFINED_DIMENTION);
    
    // success
    return 1;
}


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
void updateViewport(int w, int h) {
    // if one of the params is UNDEFINED_DIMENTIONS, ignore them.
    if (w > 0 && h > 0) {
        WINDOW_WIDTH = w;
        WINDOW_HEIGHT = h;
    }
    
    // upate
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    
    // get viewport aspect ratio
    float vwr = 1,vhr = 1;
//    if (WINDOW_WIDTH > WINDOW_HEIGHT) {
        vwr = WINDOW_WIDTH/(float)WINDOW_HEIGHT;
//    } else {
//        vhr = WINDOW_HEIGHT/(float)WINDOW_WIDTH;
//    }
    
    // reset view matrix
    SET_ORTHO_MATRIX(0, vwr, vhr, 0);
}




//// GETTERS

/**
 * @return unsigned int viewport's width in pixels
 */
unsigned int getViewportWidth() { return WINDOW_WIDTH; }

/**
 * @return unsigned int viewport's height in pixels
 */
unsigned int getViewportHeight() { return WINDOW_HEIGHT; }

/**
 * @return float viewport's aspect ratio
 */
float getAspectRatio() { return WINDOW_WIDTH/(float)WINDOW_HEIGHT; }
