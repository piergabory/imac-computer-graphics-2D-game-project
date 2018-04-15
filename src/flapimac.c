#include "../include/game.h"
#include "../include/window.h"
#include "../include/draw.h"
#include "../include/events.h"
#include "../include/messages.h"

#define WINDOW_TITLE "Flap-imac"

// framerate (minimum delay before the return of a loop call)
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(void) {
    SDL_Window *window = NULL;
    
    // initialise SDL and show a new window on screen
    if (!initWindow(&window, WINDOW_TITLE)) return 0;
    
    if (!initGame()) return 0;
    initView();
    
    // start main loop, updating the screen at a set refresh rate
    do {
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);
        
        updateGame();
        
        // execute draw
        draw();
        
        // swap window
        SDL_GL_SwapWindow(window);
        
        // wait
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    } while (eventLoop());
    
    // free SDL ressources once the loop ended
    SDL_Quit();
    
    return 1;
}
