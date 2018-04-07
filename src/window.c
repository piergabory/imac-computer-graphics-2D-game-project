#include "../include/window.h"

/*  INIT WINDOW
 *  ---------------
 *  @params: window reference, window title (text in the titlebar)
 *  Actions:
 *  - initialise SDL
 *  - create new window
 *  - initialise OpenGL context
 */
int initWindow(SDL_Window **win, char* title) {
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, ERR_SDL_INIT);
        return 0;
    }
    
    *win = NULL;
    *win = SDL_CreateWindow(
      title,                                            // titlebar text
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // x/y coordinates for window on screen (top/right corner)
      WINDOW_WIDTH,WINDOW_HEIGHT,                       // window size
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL          // fullscreen or resizable mode
    );
    
    if(*win == NULL) {
        fprintf(stderr, ERR_WINDOW_INIT);
        return 0;
    }
    
    SDL_GL_CreateContext(*win);

    return 1;
}


/*  UPDATE VIEWPORT
 *  ---------------
 *  handles resizing of the window.
 *  Updates the projection matrix to keep proportions consistent
 *  and scales the space to fit the size of the window.
 */
void updateViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    
    // get viewport aspect ratio
    float vwr = 1,vhr = 1;
    if (WINDOW_WIDTH > WINDOW_HEIGHT) {
        vwr = WINDOW_WIDTH/(float)WINDOW_HEIGHT;
    } else {
        vhr = WINDOW_HEIGHT/(float)WINDOW_WIDTH;
    }
    
    GLKMatrix4 orthoMat = GLKMatrix4MakeOrtho(0, vwr, vhr, 0, -1.0f, 1.0f);
    glLoadMatrixf(orthoMat.m);
}
