#include "view/events.h"

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
                    // shoot
                    playerStartShooting();
                    
                    // restart game if stopped
                    if (getLevel().status != 0) resetGame();
                    break;
                
                // direction keys
                case SDLK_z: case SDLK_UP: // Z key / up arrow
                    changePlayerSpeedBy(0, -1);
                    break;
                    
                case SDLK_s: case SDLK_DOWN: // S key / down arrow
                    changePlayerSpeedBy(0, 1);
                    break;
                    
                case SDLK_q: case SDLK_LEFT: // Q key / left arrow
                    changePlayerSpeedBy(-1, 0);
                    break;
                    
                case SDLK_d: case SDLK_RIGHT: // D key / right arrow
                    changePlayerSpeedBy(1, 0);
                    break;
                    
                // escape key
                case SDLK_ESCAPE:
                    // terminate program if game has ended
                    if (getLevel().status != 0) return 0;
            }
            break;
            
        case SDL_KEYUP :
            switch (e.key.keysym.sym) {
                case SDLK_z: case SDLK_UP: // Z key / up arrow
                    changePlayerSpeedBy(0, -0.1);
                    break;
                    
                case SDLK_s: case SDLK_DOWN: // S key / down arrow
                    changePlayerSpeedBy(0, 0.1);
                    break;
                    
                case SDLK_q: case SDLK_LEFT: // Q key / left arrow
                    changePlayerSpeedBy(-0.1, 0);
                    break;
                    
                case SDLK_d: case SDLK_RIGHT: // D key / right arrow
                    changePlayerSpeedBy(0.1, 0);
                    break;
                
                case SDLK_SPACE: // Spacebar
                    // shoot
                    playerStopShooting();
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
