#include "view/events.h"

/**
 * Return boolean for a key, true if pressed
 */
int getTriggerStatus(Triggers key) {
    return ActiveTriggers[key];
}

/**
 * EVENT LOOP
 * ----------
 * SDL event loop handler
 * Asks SDL for any events and handles them accordingly
 *
 * - QUIT: set loopStatus to 0 so the main loop stops and the program ends.
 * - WINDOW IS RESIZED: collects new width and height and update the window (see window.h)
 */
int eventLoop() {
    SDL_Event e;
    
    while(SDL_PollEvent(&e)) switch(e.type) {
            
        //// Keyboard Events:
        case SDL_KEYDOWN :
            switch (e.key.keysym.sym) {
                // action keys
                case SDLK_SPACE: // Spacebar
                    ActiveTriggers[SPACE] = 1;
                    
                    // restart game if stopped
                    if (getLevel().status != 0) resetGame();
                    break;
                
                // direction keys
                case SDLK_z: case SDLK_UP: // Z key / up arrow
                    ActiveTriggers[UP] = 1;
                    break;
                    
                case SDLK_s: case SDLK_DOWN: // S key / down arrow
                    ActiveTriggers[DOWN] = 1;
                    break;
                    
                case SDLK_q: case SDLK_LEFT: // Q key / left arrow
                    ActiveTriggers[LEFT] = 1;
                    break;
                    
                case SDLK_d: case SDLK_RIGHT: // D key / right arrow
                    ActiveTriggers[RIGHT] = 1;
                    break;
                    
                // escape key
                case SDLK_ESCAPE:
                    // terminate program if game has ended
                    if (getLevel().status != PLAYING) return 0;
            }
            break;
            
        case SDL_KEYUP :
            switch (e.key.keysym.sym) {
                    // action keys
                case SDLK_SPACE: // Spacebar
                    ActiveTriggers[SPACE] = 0;
                    break;
                    
                    // direction keys
                case SDLK_z: case SDLK_UP: // Z key / up arrow
                    ActiveTriggers[UP] = 0;
                    break;
                    
                case SDLK_s: case SDLK_DOWN: // S key / down arrow
                    ActiveTriggers[DOWN] = 0;
                    break;
                    
                case SDLK_q: case SDLK_LEFT: // Q key / left arrow
                    ActiveTriggers[LEFT] = 0;
                    break;
                    
                case SDLK_d: case SDLK_RIGHT: // D key / right arrow
                    ActiveTriggers[RIGHT] = 0;
                    break;
            }
            break;
            
        //// Window and Quit
        case SDL_WINDOWEVENT:
            if(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                updateViewport(e.window.data1,e.window.data2);
            break;
            
        case SDL_QUIT:
            return 0; // stop program
            break;
            
        default: break;
    }
    
    // continue
    return 1;
}
