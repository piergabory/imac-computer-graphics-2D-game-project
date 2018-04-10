#include "../include/game.h"
#include "../include/window.h"
#include "../include/draw.h"
#include "../include/events.h"
#include "../include/messages.h"

#define WINDOW_TITLE "Flap-imac"

// framerate (minimum delay before the return of a loop call)
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {
    SDL_Window *window = NULL;
    Game *flapimac;
    
    // initialise SDL and show a new window on screen
    if (!initWindow(&window, WINDOW_TITLE)) return 0;
    
    flapimac = initGame();

    // start main loop, updating the screen at a set refresh rate
    // - see draw(), static function in draw.h
    initView();
    
    int loopStatus = 1;
    while (loopStatus) {
        Uint32 startTime = SDL_GetTicks();
        glClear(GL_COLOR_BUFFER_BIT);
        
        updateGame(flapimac);
        
        // execute draw
        draw(*flapimac);
        
        // manages events
        eventLoop(flapimac->player, &loopStatus);
        
        // swap window
        SDL_GL_SwapWindow(window);
        
        // wait
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
    
    // free SDL ressources once the loop ended
    SDL_Quit();
    
    return 1;
}
