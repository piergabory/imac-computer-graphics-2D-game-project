#include "model/game.h"

#include "view/draw.h"
#include "view/events.h"

#include "support/window.h"
#include "support/messages.h"

#define WINDOW_TITLE "Flap-imac"

// framerate (minimum delay before the return of a loop call)
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(void) {
    SDL_Window *window = NULL;

    // initialize Model
    if (!initGame()) return 0;
    
    // initialise SDL and show a new window on screen
    if (!initWindow(&window, WINDOW_TITLE)) return 0;

    // initialize View
    initView();
    
    // start main loop, updating the screen at a set refresh rate
    do {
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);
        
        // update game Model
        updateGame();
        
        // update game View
        draw();
        
        // swap window
        SDL_GL_SwapWindow(window);
        
        // wait end of frame
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    } while (eventLoop());
    
    // free SDL ressources once the loop ended
    SDL_Quit();
    
    return 1;
}
